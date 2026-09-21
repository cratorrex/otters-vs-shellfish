#include "minishell.h"

int msh_export(t_shell *shell, char *var)
{
    char *key;

    if (!shell || !var)
        return (1);
    key = ft_strchr(var, '=');
    if (get_target_variable_index(shell->envp, key) != -1)
        shell->envp = update_variable(shell->envp, var);
    else
        shell->envp = add_new_variable(shell->envp, var);
    return (0);
}