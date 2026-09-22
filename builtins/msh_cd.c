/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 17:00:04 by thtay             #+#    #+#             */
/*   Updated: 2026/08/14 17:00:07 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static int	cd_home(t_shell *shell)
{
	char	*home;

	home = get_env_value("HOME", shell->env);
	if (!home)
	{
		ft_putstr_fd("msh: cd: HOME not set\n", 2);
		return (1);
	}
	return (cd_change_dir(shell, home, 0));
}

static int	cd_oldpwd(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = get_env_value("OLDPWD", shell->env);
	if (!oldpwd)
	{
		ft_putstr_fd("msh: cd: OLDPWD not set\n", 2);
		return (1);
	}
	return (cd_change_dir(shell, oldpwd, 1));
}

static int	cd_tilde(t_shell *shell)
{
	char	*home;

	home = get_env_value("HOME", shell->env);
	if (!home)
	{
		ft_putstr_fd("msh: cd: HOME not set\n", 2);
		return (1);
	}
	return (cd_change_dir(shell, home, 0));
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
	if (ft_strlen(av[1]) == 1 && av[1][0] == '~')
		return (cd_tilde(shell));
	if (ft_strlen(av[1]) == 1 && av[1][0] == '-')
		return (cd_oldpwd(shell));
	return (cd_change_dir(shell, av[1], 0));
}

/*
char *getcwd() //maybe for pwd
int   chdir(const char *path)
	0 else -1 and ERRNO
	EACCES
	ENOENT
	ENOTDIR

Exit cases:
cd: too many arguments >> 1
cd: {invalDIR}: No such file or directory >> 1
cd: {invalDIR}: Not a directory >> 1
cd: {invalDIR}: Permission denied >> 1 >> needs +x
>  cd in current directory but lost permissions incl.

niche case
changing of $PWD does nothing (at all, it seems)

posix case
cd follows the symlink :O (-L)

cd with only a relative or absolute path
case no need to handle "-" (back)
*/

// int	mcd_check_fx_ok(char *dir)
// {
// 	if (access(dir, F_OK))
// 		return (printf("msh: cd: %s: No such file or directory\n",
// 				dir), 1);
// 	else if (access(dir, X_OK))
// 		return (printf("msh: cd: %s: Permission denied\n",
// 				dir), 1);
// 	return (0);
// }

// int	msh_cd(int count, char **string)
// {
// 	//char	*co_pwd[2];

// 	if (count > 2)
// 		return (printf("msh: cd: too many arguments\n"), 1);
// 	if (count == 2 && *(string[1]) != 0)
// 	{
// 		if (mcd_check_fx_ok(string[1]) > 0)
// 			return (1);
// 		// co_pwd[0] = getenv("PWD");
// 		// co_pwd[1] = getenv("OLDPWD");
// 		if (chdir(string[1]) == 0)
// 			return (0);
// 		else
// 			return (perror("msh: cd:"), 1);
// 	}
// 	else //find home if only `cd` or `cd `
// 	{
// 		return (0);
// 	}
// }
