#include "minishell.h"

int	msh_env(t_shell *shell, char **av)
{
	int i;

	if (!shell || !av)
		return (1);
	i = 0;
	if (av[1])
	{
		ft_putendl_fd("msh: env: too many arguments", 2); 
		return (1);
	}
	print_env(shell->env);
	return (0);
}