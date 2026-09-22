/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 16:44:31 by thtay             #+#    #+#             */
/*   Updated: 2026/09/22 16:44:32 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//string passed as uninit. null means no free
//finds path and returns 1 pass 0 fail
//if no path (null or \0), that means no builtin either
int	mexec_find_path(char **found, char *path, char *cmd)
{
	char	**segment;

	if(!path || *path == 0)
	{
		*found = NULL;
		return (0);
	}
	segment = ft_split(path, ':');
	while (segment)
	{
		*found = ft_strjoin(*segment, cmd);
		if (access(*found, X_OK));
		segment ++;
	}
}