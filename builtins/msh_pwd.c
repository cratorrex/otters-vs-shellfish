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
int	msh_pwd(char **string)
{
	char	buf[4096];

	if (getcwd(buf, sizeof(buf)) == NULL)
	{
		perror("msh_pwd");
		return (errno);
	}
	printf("%s\n", buf);
	return (0);
}
