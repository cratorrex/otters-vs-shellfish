#include "minishell.h"

t_redir *redir_new(t_token_type type, char *target)
{
    t_redir *node;

    node = malloc(sizeof(t_redir));
    if (!node)
        return (NULL);
    node->target = ft_strdup(target);
    if (!node->target)
    {
        free(node);
        return (NULL);
    }
    node->type = type;
    node->next = NULL;
    return (node);
}

void redir_add_back(t_redir **head, t_redir *new)
{
    t_redir *current_node;

    if (!*head)
    {
        *head = new;
        return ;
    }
    current_node = *head;
    while (current_node->next)
        current_node = current_node->next;
    current_node->next = new;
}

