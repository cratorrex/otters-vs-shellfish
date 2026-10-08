/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_key.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 15:17:43 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/08 15:17:46 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_target_variable_index(char **existing_env, char *target_var)
{
	int	len;
	int	i;

	if (!existing_env || !target_var)
		return (-1);
	len = ft_strlen(target_var);
	i = 0;
	while (existing_env[i])
	{
		if (ft_strncmp(existing_env[i], target_var, len) == 0
			&& existing_env[i][len] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*get_env_key(char *var)
{
	char	*equal;

	if (!var)
		return (NULL);
	equal = ft_strchr(var, '=');
	if (!equal)
		return (ft_strdup(var));
	return (ft_substr(var, 0, equal - var));
}
