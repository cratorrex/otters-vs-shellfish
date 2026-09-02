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

int	mcd_check_fx_ok(char *dir)
{
	if (access(dir, F_OK))
		return (printf("msh: cd: %s: No such file or directory\n",
				dir), 1);
	else if (access(dir, X_OK))
		return (printf("msh: cd: %s: Permission denied\n",
				dir), 1);
	return (0);
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
cd: {invalDIR}: Permission denied >> 1 >> needs +x

niche case
changing of $PWD does nothing (at all, it seems)

posix case
cd follows the symlink :O (-L)

cd with only a relative or absolute path
case no need to handle "-" (back)
*/
int	msh_cd(int count, char **string)
{
	char	*co_pwd[2];

	if (count > 2)
		return (printf("msh: cd: too many arguments\n"), 1);
	if (count == 2)
	{
		if (mcd_check_fx_ok(string[1]))
			return (1);
		// co_pwd[0] = getenv("PWD");
		// co_pwd[1] = getenv("OLDPWD");
		if (chdir(string[1]) == 0)
			return (0);
		else
			return (perror("msh_cd"), 1);
	}
	return (0);
}
