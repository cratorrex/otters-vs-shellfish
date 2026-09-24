#include "minishell.h"

t_builtin_cmd is_builtin_cmd(char *cmd)
{
    //int is_match;
    
    if (ft_strncmp(cmd, "echo", 5) == 0)
        return (ECHO);
    if (ft_strncmp(cmd, "cd", 3) == 0)
        return (CD);
    if (ft_strncmp(cmd, "pwd", 4) == 0)
        return (PWD);
    if (ft_strncmp(cmd, "export", 7) == 0)
        return (EXPORT);
    if (ft_strncmp(cmd, "unset", 6) == 0)
        return (UNSET);
    if (ft_strncmp(cmd, "env", 4) == 0)
        return (ENV);
    if (ft_strncmp(cmd, "exit", 5) == 0)
        return (EXIT);
    return (UNKNOWN_CMD);
}