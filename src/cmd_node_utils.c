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

int parse_command(t_token **tokens, t_cmd *cmd)
{
	t_token *current;
	t_redir *new_redir;

	if (!*tokens || !cmd)
		return (0);
	current = *tokens;
	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type == TOKEN_WORD)
		{
			if (!cmd_add_args(current->value, cmd))
				return (0);
		}
		else if (is_redirection(current->type))
		{
			new_redir = redir_new(current->type, current->next->value);
			redir_add_back(&cmd->redirs, new_redir);
			current = current->next;
		}
		current = current->next;
	}
	*tokens = current;
	return (1);
}

void display_new_cmd(t_cmd *cmd)
{
	int i;
	int j;
	printf("cmd->av\n");
	j = 0;
	i = 0;
	while (cmd)
	{
		printf("cmd %d\n", i);
		while (cmd->av[j])
		{
			printf("cmd->av[%d] = %s\n", j, cmd->av[j]);
			j++;
		}
		while (cmd->redirs)
		{
			printf("cmd->redirs type = %d | target = %s\n", cmd->redirs->type, cmd->redirs->target);
			cmd->redirs = cmd->redirs->next;
		}
		cmd = cmd->next;
		i++;
	}
}

t_cmd *parse_token(t_token *tokens)
{
	t_cmd *head_cmd;
	t_cmd *new_cmd;

	if (!tokens)
		return (NULL);
	head_cmd = NULL;
	while (tokens)
	{
		new_cmd = cmd_new();
		if (!new_cmd)
			return (NULL);
		if (!parse_command(&tokens, new_cmd))
		{
			/* free up memory here */
			return (NULL);
		}
		cmd_add_back(&head_cmd, new_cmd);
		display_new_cmd(new_cmd);
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (head_cmd);
}


// int get_av_count(t_token *tokens)
// {
// 	int count;
// 	t_token *current;

// 	if (!tokens || !tokens)
// 		return (-1);
// 	current = tokens;
// 	count = 0;
// 	while (current)
// 	{
// 		if (current->type == TOKEN_WORD)
// 			count++;
// 		else if (is_redirection(current->type))
// 			current = current->next;
// 		else
// 			break ;
// 		current = current->next;
// 	}
// 	return (count);
// }

// void initialize_command(t_token **tokens, t_cmd **cmd)
// {
// 	int i;
// 	t_token *current;
// 	t_redir *head_redir;
// 	t_redir *new_redir;

// 	head_redir = NULL;
// 	(*cmd)->av = malloc(sizeof(char *) * (get_av_count(*tokens) + 1));
// 	if (!(*cmd)->av)
// 		return ;
// 	current = *tokens;
// 	i = 0;
// 	while (current && current->type != TOKEN_PIPE)
// 	{
// 		if (current->type == TOKEN_WORD)
// 		{
// 			(*cmd)->av[i++] = ft_strdup(current->value);
// 			/* freed up memory if failed */
// 		}
// 		else if (is_redirection(current->type))
// 		{
// 			new_redir = redir_new(current->type, current->next->value);
// 			redir_add_back(&head_redir, new_redir);
// 			current = current->next;
// 		}
// 		current = current->next;
// 	}
// 	*tokens = current;
// 	(*cmd)->av[i] = NULL;
// 	(*cmd)->redirs = head_redir;
// }



// t_cmd *parse_token(t_token *tokens)
// {
// 	t_token *tmp;
// 	t_cmd *head_cmd;
// 	t_cmd *new_cmd;

// 	if (!tokens)
// 		return (NULL);
// 	tmp = tokens;
// 	head_cmd = NULL;
// 	new_cmd = NULL;
// 	if (tmp->type == TOKEN_WORD)
// 		new_cmd = cmd_new();
// 	while (tmp)
// 	{
// 		initialize_command(&tmp, &new_cmd);
// 		display_new_cmd(new_cmd);
// 		cmd_add_back(&head_cmd, new_cmd);
// 		if (tmp->type == TOKEN_PIPE)
// 			new_cmd = cmd_new();
// 		tmp = tmp->next;
// 	}
// 	return (head_cmd);
// }