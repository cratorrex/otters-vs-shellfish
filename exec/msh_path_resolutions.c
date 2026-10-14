/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_path_resolutions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 14:22:27 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/11 14:22:44 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_value(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}

char	*join_path_command(char *directory, size_t dir_len, char *cmd0)
{
	char	*prefix;
	char	*full;

	if (dir_len == 0)
		prefix = ft_strdup(".");
	else
		prefix = ft_substr(directory, 0, dir_len);
	if (!prefix)
		return (NULL);
	full = ft_strjoin(prefix, "/");
	free(prefix);
	if (!full)
		return (NULL);
	prefix = ft_strjoin(full, cmd0);
	free(full);
	return (prefix);
}

char	*search_path_directories(char *path, char *cmd0)
{
	char	*candidate;
	size_t	start;
	size_t	end;

	start = 0;
	while (1)
	{
		end = start;
		while (path[end] && path[end] != ':')
			end++;
		candidate = join_path_command(path + start, end - start, cmd0);
		if (!candidate)
			return (NULL);
		if (access(candidate, X_OK) == 0)
			return (candidate);
		free(candidate);
		if (!path[end])
			break ;
		start = end + 1;
	}
	return (NULL);
}

char	*resolve_command_path(char *cmd0, char **env)
{
	char	*path;
	char	*result;

	if (!cmd0 || !cmd0[0])
		return (NULL);
	if (ft_strchr(cmd0, '/'))
		return (ft_strdup(cmd0));
	path = get_path_value(env);
	if (!path)
		return (NULL);
	result = search_path_directories(path, cmd0);
	free(path);
	return (result);
}
