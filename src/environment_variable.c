/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <jatansil@42mail.sutd.edu.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:00:50 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/01 16:08:48 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**freed_up_env(int index, char **env)
{
	while (index > 0)
		free(env[--index]);
	free(env);
	return (NULL);
}

void	freed_up_existing_env(char **existing_env)
{
	int	i;

	if (!existing_env)
		return ;
	i = 0;
	while (existing_env[i])
		free(existing_env[i++]);
	free(existing_env);
}

char	**init_env_variable(char **envp)
{
	int		i;
	int		j;
	char	**env_variable;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	env_variable = malloc(sizeof(char *) * (i + 1));
	if (!env_variable)
		return (NULL);
	j = 0;
	while (envp[j])
	{
		env_variable[j] = ft_strdup(envp[j]);
		if (!env_variable[j])
			return (freed_up_env(j, env_variable));
		j++;
	}
	env_variable[j] = NULL;
	return (env_variable);
}

char	**add_new_variable(char **existing_env, char *new_var)
{
	int		i;
	char	**new_env;

	if (!existing_env || !new_var)
		return (NULL);
	i = 0;
	while (existing_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (existing_env[i])
	{
		new_env[i] = ft_strdup(existing_env[i]);
		if (!new_env[i])
			return (freed_up_env(i, new_env));
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	if (!new_env[i])
		return (freed_up_env(i, new_env));
	new_env[++i] = NULL;
	freed_up_existing_env(existing_env);
	return (new_env);
}

char	**update_variable(char **existing_env, char *var)
{
	int		index;
	char	*new_var;
	char	*key;

	if (!existing_env || !var)
		return (NULL);
	key = get_env_key(var);
	if (!key)
		return (NULL);
	index = get_target_variable_index(existing_env, key);
	free(key);
	if (index == -1)
		return (existing_env);
	new_var = ft_strdup(var);
	if (!new_var)
		return (NULL);
	free(existing_env[index]);
	existing_env[index] = new_var;
	return (existing_env);
}
