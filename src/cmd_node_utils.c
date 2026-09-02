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

int cmd_add_args(char *value, t_cmd *cmd)
{
	int count;
	int i;
	char **new_av;

	if (!value || !cmd)
		return (0);
	count = 0;
	while (cmd->av && cmd->av[count])
		count++;
	new_av = malloc(sizeof(char *) * (count + 2));
	if (!new_av)
		return (0);
	i = 0;
	while (i < count)
	{
		new_av[i] = cmd->av[i];
		i++;
	}
	new_av[count] = ft_strdup(value);
	if (!new_av[count])
	{
		free(new_av);
		return (0);
	}
	new_av[count + 1] = NULL;

	free(cmd->av);
	cmd->av = new_av;
	return (1);
}