#include "minishell.h"

static int	is_var_start(char c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| c == '_');
}

static int	is_var_char(char c)
{
	return ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| c == '_');
}

char	*get_env_value(char *name, char **envp)
{
	int	i;
	int	len;

	i = 0;
	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0
			&& envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

char	*expand_variable(char *str, int *i, t_shell *shell)
{
	int		start;
	int		len;
	char	*name;
	char	*value;

	(*i)++;

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->exit_status));
	}

	if (!is_var_start(str[*i]))
		return (ft_strdup("$"));

	start = *i;
	while (str[*i] && is_var_char(str[*i]))
		(*i)++;

	len = *i - start;
	name = ft_substr(str, start, len);
	if (!name)
		return (NULL);

	value = get_env_value(name, shell->envp);
	free(name);
	return (value);
}