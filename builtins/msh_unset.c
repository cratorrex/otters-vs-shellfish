#include "minishell.h"

int msh_unset(t_shell *shell, char *var)
{
    if (!shell)
        return (1);
    shell->envp = remove_variable(shell->envp, var);
    if (!shell->envp)
        return (1);
    return (0);
}