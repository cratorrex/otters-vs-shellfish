/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 20:22:28 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/12 20:22:37 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_shell(t_shell *shell, char **envp)
{
	if (!shell || !envp)
		return (0);
	shell->env = init_env_variable(envp);
	if (!shell->env)
		return (0);
	shell->exit_status = 0;
	shell->should_exit = 0;
	return (1);
}

void	set_shell_level(t_shell *shell, char *shlvl)
{
	int		lvl;
	char	**av;
	char	*res;
	int		i;

	lvl = ft_atoi(shlvl);
	free(shlvl);
	lvl ++;
	shlvl = ft_itoa(lvl);
	res = ft_strjoin("export SHLVL=", shlvl);
	av = ft_split(res, ' ');
	msh_export(shell, av);
	free(res);
	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
	free(shlvl);
}
