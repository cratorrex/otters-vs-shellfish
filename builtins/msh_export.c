#include "minishell.h"

int	msh_export(t_shell *shell, char *var)
{
	char	*key;
	char	**new_env;
	int		index;

	if (!shell || !var)
		return (1);
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