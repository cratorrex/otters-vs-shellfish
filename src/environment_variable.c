#include "minishell.h"

static char	**freed_up_env(int index, char **env)
{
	while (index > 0)
		free(env[--index]);
	free(env);
	return (NULL);
}


static void	freed_up_existing_env(char **existing_env)
{
	int	i;

	if (!existing_env)
		return ;
	i = 0;
	while (existing_env[i])
		free(existing_env[i++]);
	free(existing_env);
}

char **init_env_variable(char **envp)
{
    int i;
    int j;
    char **env_variable;

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
	int		j;
	char	**new_env;

	if (!existing_env || !new_var)
		return (NULL);
	i = 0;
	while (existing_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	j = 0;
	while (existing_env[j])
	{
		new_env[j] = ft_strdup(existing_env[j]);
		if (!new_env[j])
			return (freed_up_env(j, new_env));
		j++;
	}
	new_env[j] = ft_strdup(new_var);
	if (!new_env[j])
		return (freed_up_env(j, new_env));
	new_env[++j] = NULL;
	freed_up_existing_env(existing_env);
	return (new_env);
}

int get_target_variable_index(char **existing_env, char *target_var)
{
    int len;
    int i;

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

char	**remove_variable(char **existing_env, char *var)
{
	int		count;
	int		remove_at;
	int		i;
	int		j;
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
	i = 0;
	j = 0;
	while (existing_env[i])
	{
		if (i != remove_at)
		{
			new_env[j] = ft_strdup(existing_env[i]);
			if (!new_env[j])
				return (freed_up_env(j, new_env));
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	freed_up_existing_env(existing_env);
	return (new_env);
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
