/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <jatansil@42mail.sutd.edu.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:51:00 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/01 16:53:41 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static char	**create_new_av(char **av, char *value)
{
	int		count;
	int		i;
	char	**new_av;

	count = 0;
	while (av && av[count])
		count++;
	new_av = malloc(sizeof(char *) * (count + 2));
	if (!new_av)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_av[i] = av[i];
		i++;
	}
	new_av[count] = ft_strdup(value);
	if (!new_av[count])
	{
		free(new_av);
		return (NULL);
	}
	new_av[count + 1] = NULL;
	return (new_av);
}

int	cmd_add_args(char *value, t_cmd *cmd)
{
	char	**new_av;

	if (!value || !cmd)
		return (0);
	new_av = create_new_av(cmd->av, value);
	if (!new_av)
		return (0);
	free(cmd->av);
	cmd->av = new_av;
	return (1);
}
