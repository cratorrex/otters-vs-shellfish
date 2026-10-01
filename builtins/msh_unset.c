/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <jatansil@42mail.sutd.edu.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 17:29:30 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/01 17:29:56 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_unset(t_shell *shell, char **av)
{
	char	**new_env;
	int		i;

	if (!shell || !av)
		return (1);
	i = 1;
	while (av[i])
	{
		new_env = remove_variable(shell->env, av[i]);
		if (!new_env)
			return (1);
		shell->env = new_env;
		i++;
	}
	return (0);
}
