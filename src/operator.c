#include "minishell.h"

t_token_type classify_operator(char *line)
{
    int i;

    i = 0;
    if (line[i] == '|')
        return (TOKEN_PIPE);
    if (line[i] == '<' && line[i + 1] == '<')
		return (TOKEN_HEREDOC);
    if (line[i] == '>' && line[i + 1] == '>')
        return (TOKEN_APPEND);
    if (line[i] == '<')
		return (TOKEN_REDIR_IN);
	if (line[i] == '>')
		return (TOKEN_REDIR_OUT);
    return (TOKEN_WORD);
}