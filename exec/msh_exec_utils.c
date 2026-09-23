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

void	mexec_free_segment(char **segment)
{
	int	i;

	i = 0;
	while (segment[i] != NULL)
	{
		free(segment[i]);
		i ++;
	}
	free(segment[i]);
	free(segment);
}

//string passed as uninit. null means no free
//finds path and returns 1 pass 0 fail
//if no path (null or \0), that means no builtin either
// `found will be overwritten/malloced`
// `function does not currently check if found is malloced`
int	mexec_find_path(char **found, char *path, char *cmd0)
{
	char	**segment;
	char	*cmd;
	int		i;

	i = 0;
	if(!path || *path == 0)
	{
		*found = NULL;
		return (0);
	}
	segment = ft_split(path, ':');
	cmd = ft_strjoin("/", cmd0);
	while (segment[i] != NULL)
	{
		*found = ft_strjoin(segment[i], cmd);
		if (access(*found, X_OK) == 0)
			return (mexec_free_segment(segment), free(cmd), 1);
		free(*found);
		i ++;
	}
	*found = NULL;
	return (mexec_free_segment(segment), free(cmd), 0);
}

/* int main(int c, char **v)
{
	char *find;
	char *path;
	
	path = getenv("PATH");
	if (c == 2)
	{
		if (mexec_find_path(&find, path, v[1]))
			printf("%s\n", find);
		else
			printf("0\n");
		free(find);
	}
} */