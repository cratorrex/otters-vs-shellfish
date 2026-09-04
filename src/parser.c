#include "minishell.h"

int validate_syntax(t_token *tokens)
{
    t_token *current;

    if (!tokens)
        return (0);
    current = tokens;
    if (current->type == TOKEN_PIPE)
        return (0);
    while (current)
    {
        if (current->type == TOKEN_PIPE)
        {
            if (!current->next)
                return (0);
            if (current->next->type == TOKEN_PIPE)
                return (0);
        }
        if (is_redirection(current->type))
        {
            if (!current->next)
                return (0);
            if (current->next->type != TOKEN_WORD)
                return (0);
        }
        current = current->next;
    }
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
			token_clear(&tokens);
			free(new_cmd);
			return (NULL);
		}
		cmd_add_back(&head_cmd, new_cmd);
		if (tokens && tokens->type == TOKEN_PIPE)
			tokens = tokens->next;
	}
	return (head_cmd);
}