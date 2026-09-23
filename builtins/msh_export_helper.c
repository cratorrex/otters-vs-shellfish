#include "minishell.h"

static int	env_count(char **env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i])
		i++;
	return (i);
}

static char	**copy_env(char **env)
{
	char	**copy;
	int		i;
	int		count;

	count = env_count(env);
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	env_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	sort_export_env(char **env)
{
	int		i;
	int		j;
	int		count;
	char	*tmp;

	count = env_count(env);
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (env_strcmp(env[j], env[j + 1]) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_variable(char *var)
{
	char	*equal;

	equal = ft_strchr(var, '=');
	if (!equal)
	{
		printf("declare -x %s\n", var);
		return ;
	}
	printf("declare -x ");
	printf("%.*s", (int)(equal - var), var);
	printf("=\"%s\"\n", equal + 1);
}

void free_env(char **env)
{
    int i;

    i = 0;
    while (env[i])
        free(env[i++]);
    free(env);
}

int	print_export(char **env)
{
	char	**copy;
	int		i;

	copy = copy_env(env);
	if (!copy)
		return (1);
	sort_export_env(copy);
	i = 0;
	while (copy[i])
	{
		print_export_variable(copy[i]);
		i++;
	}
	free_env(copy);
	return (0);
}