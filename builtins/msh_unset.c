#include "minishell.h"

int	msh_unset(t_shell *shell, char **av)
{
	char	**new_env;
	int		i;

	if (!shell || !av)
		return (1);
	i = 1;
	while (av[i])
	{
		new_env = remove_variable(shell->env, av[i]);
		if (!new_env)
			return (1);
		shell->env = new_env;
		i++;
	}
	return (0);
}