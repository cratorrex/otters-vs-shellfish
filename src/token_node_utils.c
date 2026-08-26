#include "minishell.h"

t_token *token_new(char *value, t_token_type type)
{
    t_token *node;
    if (!value)
        return (NULL);
    node = malloc(sizeof(t_token));
    if (!node)
        return (NULL);
    node->value = ft_strdup(value);
    if (!node->value)
    {
        free(node);
        return (NULL);
    }
    node->type = type;
    node->next = NULL;
    return (node);
}

void token_add_back(t_token **head, t_token *new)
{
    t_token *current_node;

    if (!*head)
    {
        *head = new;
        return ;
    }
    current_node = *head;
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
        if ((*lst)->value)
            free(((*lst)->value));
        free(*lst);
        *lst = tmp;
    }
    *lst = NULL;
}