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