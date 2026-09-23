#include "minishell.h"

static int	isvalid_key_identifier(char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	isvalid_export_arg(char *arg)
{
	char	*key;

	if (!arg)
		return (0);
	key = get_env_key(arg);
	if (!key)
		return (0);
	if (!isvalid_key_identifier(key))
	{
		printf("msh: export: `%s': not a valid identifier\n", arg);
		free(key);
		return (0);
	}
	free(key);
	if (ft_strchr(arg, '='))
		return (1);
	return (2);
}

static int	export_one_variable(t_shell *shell, char *var)
{
	char	*key;
	char	**new_env;
	int		index;

	key = get_env_key(var);
	if (!key)
		return (1);
	index = get_target_variable_index(shell->env, key);
	free(key);
	if (index != -1)
		new_env = update_variable(shell->env, var);
	else
		new_env = add_new_variable(shell->env, var);
	if (!new_env)
		return (1);
	shell->env = new_env;
	return (0);
}

static int	export_key_only(t_shell *shell, char *key)
{
	char	*entry;
	char	**new_env;
	int		index;

	index = get_target_variable_index(shell->env, key);
	if (index != -1)
		return (0);
	entry = ft_strjoin(key, "=");
	if (!entry)
		return (1);
	new_env = add_new_variable(shell->env, entry);
	free(entry);
	if (!new_env)
		return (1);
	shell->env = new_env;
	return (0);
}

int	msh_export(t_shell *shell, char **av)
{
	int	i;
	int	status;
	int	valid;

	if (!shell || !av)
		return (1);
	if (!av[1])
		return (print_export(shell->env));
	i = 1;
	status = 0;
	while (av[i])
	{
		valid = isvalid_export_arg(av[i]);
		if (valid == 0)
			status = 1;
		else if (valid == 1)
		{
			if (export_one_variable(shell, av[i]))
				status = 1;
		}
		else if (valid == 2)
		{
			if (export_key_only(shell, av[i]))
				status = 1;
		}
		i++;
	}
	return (status);
}