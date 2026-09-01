#include "minishell.h"

t_builtin_cmd is_builtin_cmd(char *cmd)
{
    int is_match;
    
    if (ft_strcmp(cmd, "echo") == 0)
        return (ECHO);
    if (ft_strcmp(cmd, "cd") == 0)
        return (CD);
    if (ft_strcmp(cmd, "pwd") == 0)
        return (PWD);
    if (ft_strcmp(cmd, "export") == 0)
        return (EXPORT);
    if (ft_strcmp(cmd, "unset") == 0)
        return (UNSET);
    if (ft_strcmp(cmd, "env") == 0)
        return (ENV);
    if (ft_strcmp(cmd, "exit") == 0)
        return (EXIT);
    return (UNKNOWN_CMD);
}