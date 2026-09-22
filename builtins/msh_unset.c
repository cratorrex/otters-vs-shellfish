#include "minishell.h"

int	msh_unset(t_shell *shell, char *var)
{
	char	**new_env;

	if (!shell || !var)
		return (1);
	new_env = remove_variable(shell->env, var);
	if (!new_env)
		return (1);
	shell->env = new_env;
	return (0);
}