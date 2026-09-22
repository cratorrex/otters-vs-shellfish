#include "minishell.h"

int msh_unset(t_shell *shell, char *var)
{
    if (!shell)
        return (1);
    shell->env = remove_variable(shell->env, var);
    if (!shell->env)
        return (1);
    return (0);
}