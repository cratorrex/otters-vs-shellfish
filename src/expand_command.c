#include "minishell.h"

static int expand_argvs(t_cmd *cmd, t_shell *shell)
{
    int i;
    char *old_str;
    char *new_str;

    i = 0;
    while (cmd->av[i])
    {
        old_str = cmd->av[i];
        new_str = expand_word(cmd->av[i], shell);
        if (!new_str) 
            return (0);
        free(old_str);
        cmd->av[i] = new_str;
        i++;
    }
    return (1);
}

static int expand_redirs(t_cmd *cmd, t_shell *shell)
{
    t_redir *redir;
    
    char *old_str; 
    char *new_str; 
    redir = cmd->redirs; 
    
    while (redir) 
    { 
        old_str = redir->target; 
        new_str = expand_word(old_str, shell);
        if (!new_str) 
            return (0); 
        free(old_str); 
        redir->target = new_str;
        redir = redir->next; 
    } 
    return (1);
}

int expand_command(t_cmd *cmd, t_shell *shell)
{
    while (cmd)
    {
        if (!expand_argvs(cmd, shell))
            return (0);
        if (!expand_redirs(cmd, shell))
            return (0);
        cmd = cmd->next;
    }
    return (1);
}