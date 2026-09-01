/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 17:00:10 by thtay             #+#    #+#             */
/*   Updated: 2026/08/14 17:00:11 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//literally just prints out the current working directory
//ERROR: If the buffer is not big enough (imagine...)
//ENOENT
//
//assumption: we are allowed to use the MACRO errno
//pwd accepts any number of arguments, but disregards them...
int	msh_pwd(int count, char **string)
{
	char	buf[4096];

	if (count && string)
	{
		if (getcwd(buf, sizeof(buf)) == NULL)
		{
			perror("pwd");
			return (errno);
		}
		printf("%s\n", buf);
	}
	return (0);
}

/*
Additional rebase
code the variant that takes in env and then prints out $PWD
// match envp for $PWD and print it (using write)
since PWD=[...], printf +4 
*/
int	msh_pwd_envp(int count, char **string, char **envp)
{
	if (count && string && envp)
	{
		
	}
	return 0;
}
