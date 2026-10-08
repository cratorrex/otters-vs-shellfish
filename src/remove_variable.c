/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 14:55:20 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/08 14:55:41 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_without_variable(char **existing_env, char **new_env,
		int remove_at)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (existing_env[i])
	{
		if (i != remove_at)
		{
			new_env[j] = ft_strdup(existing_env[i]);
			if (!new_env[j])
				return (freed_up_env(j, new_env), 0);
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	return (1);
}

char	**remove_variable(char **existing_env, char *var)
{
	int		count;
	int		remove_at;
	char	**new_env;

	if (!existing_env || !var)
		return (NULL);
	remove_at = get_target_variable_index(existing_env, var);
	if (remove_at == -1)
		return (existing_env);
	count = 0;
	while (existing_env[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	if (!copy_without_variable(existing_env, new_env, remove_at))
		return (NULL);
	freed_up_existing_env(existing_env);
	return (new_env);
}
