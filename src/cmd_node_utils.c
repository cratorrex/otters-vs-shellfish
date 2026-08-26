#include "minishell.h"

t_cmd	*cmd_new(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->av = NULL;
	node->redirs = NULL;
	node->next = NULL;
	return (node);
}

void	cmd_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*current_node;

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