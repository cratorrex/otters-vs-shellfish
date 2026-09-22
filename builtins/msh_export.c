#include "minishell.h"

int msh_export(t_shell *shell, char *var)
{
    char *key;

    if (!shell || !var)
        return (1);
    key = ft_strchr(var, '=');
    if (get_target_variable_index(shell->env, key) != -1)
        shell->env = update_variable(shell->env, var);
    else
        shell->env = add_new_variable(shell->env, var);
    return (0);
}