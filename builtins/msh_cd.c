/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 17:00:04 by thtay             #+#    #+#             */
/*   Updated: 2026/10/01 17:20:36 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(t_shell *shell)
{
	char	*home;
	int		res;

	home = get_env_value("HOME", shell->env);
	if (!home)
	{
		ft_putstr_fd("msh: cd: HOME not set\n", 2);
		return (1);
	}
	res = cd_change_dir(shell, home, 0);
	return (free(home), res);
}

static int	cd_oldpwd(t_shell *shell)
{
	char	*oldpwd;
	int		res;

	oldpwd = get_env_value("OLDPWD", shell->env);
	if (!oldpwd)
	{
		ft_putstr_fd("msh: cd: OLDPWD not set\n", 2);
		return (1);
	}
	res = cd_change_dir(shell, oldpwd, 1);
	return (free(oldpwd), res);
}

static int	mcd_check_fx_ok(char *dir)
{
	DIR	*directory;

	if (access(dir, F_OK) == -1)
		return (ft_putstr_fd("msh: cd: ", 1),
			ft_putstr_fd(dir, 1), ft_putstr_fd(":", 1),
			ft_putstr_fd(" No such file or directory\n", 2), 1);
	directory = opendir(dir);
	if (!directory)
	{
		printf("msh: cd: %s:", dir);
		if (access(dir, X_OK) == -1)
			return (printf(" Permission denied\n"), 1);
		else
			return (printf(" Not a directory\n"), 1);
	}
	closedir(directory);
	return (0);
}

int	msh_cd(t_shell *shell, char **av)
{
	int	count;

	if (!shell || !av)
		return (1);
	count = 0;
	while (av[count])
		count++;
	if (count > 2)
	{
		ft_putstr_fd("msh: cd: too many arguments\n", 2);
		return (1);
	}
	if (count == 1)
		return (cd_home(shell));
	if (ft_strlen(av[1]) == 1 && av[1][0] == '-')
		return (cd_oldpwd(shell));
	if (mcd_check_fx_ok(av[1]))
		return (1);
	return (cd_change_dir(shell, av[1], 0));
}
