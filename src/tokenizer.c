#include "minishell.h"

int get_pipe_index(char *line_read)
{
    if (!line_read)
        return (-1);
    
    return (0);
}
t_token_type classify_token()
{
    return (TOKEN_WORD);
}
t_token *token_new(char *value, t_token_type type)
{
    if (!value)
        return (NULL);
    t_token *node = malloc(sizeof(t_token));
    if (!node)
        return (NULL);
    node->value = value;
    node->type = type;
    node->next = NULL;
    return (node);
}

void token_add_back(t_token **lst, t_token *new)
{
    t_token *current_node;

    current_node = *lst;
    if (!current_node || !new)
        return ;
    while (current_node->next != NULL)
        current_node = current_node->next;
    current_node->next = new;
}

void token_clear(t_token **lst)
{
    t_token *tmp;

    if (!lst)
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        // if ((*lst)->value)
        //     free(((*lst)->value));
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}



void process_raw_line(char *line_read)
{
    printf("%s\n", line_read);
    
    /* For testing only, remove this later */
    


    
}