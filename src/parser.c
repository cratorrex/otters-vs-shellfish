#include "minishell.h"

char *rl_gets(void)
{
	char *line_read;

	line_read = readline("urprompt>");
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}

void free_line_buffer(char **line_buffer)
{
    if (*line_buffer)
    {
        free(*line_buffer);
        *line_buffer = NULL;
    }
}

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