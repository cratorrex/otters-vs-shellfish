#include "minishell.h"

int get_pipe_index(char *line_read)
{
    if (!line_read)
        return (-1);
    
    return (0);
}

t_token *token_new(char *value, t_token_type type)
{
    t_token *head;
    if (!value)
        return (NULL);
    head = NULL;
}


void process_raw_line(char *line_read)
{
    printf("%s\n", line_read);
    
    int i;
    char **split_cmd;
    
    i = 0;
    split_cmd = ft_split(line_read, '|');
    if (!split_cmd || !*split_cmd)
    {
        return ;
    }
    while (split_cmd[i])
    {
        printf("split_cmd[%d] = %s\n", i, split_cmd[i]);
        i++;
    }
    free(split_cmd);
}