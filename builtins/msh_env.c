#include "minishell.h"

int msh_env(t_shell *shell)
{
    if (!shell)
        return (1);
    print_env(shell->envp);
    return (0);
}