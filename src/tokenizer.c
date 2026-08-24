#include "minishell.h"

char *read_token(char *line, int *i)
{
    t_quote_state quote;
    int           start;
    int           end;
    char          *word;

    quote = QUOTE_NONE;
    start = *i;
    while (line[*i])
    {
        if (quote == QUOTE_NONE)
        {
            if (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
                break ;
            else if (line[*i] == '\'')
                quote = QUOTE_SINGLE;
            else if (line[*i] == '"')
                quote = QUOTE_DOUBLE;
        }
        else if (quote == QUOTE_SINGLE)
        {
            if (line[*i] == '\'')
                quote = QUOTE_NONE;
        }
        else if (quote == QUOTE_DOUBLE)
        {
            if (line[*i] == '"')
                quote = QUOTE_NONE;
        }
        (*i)++;
    }
    if (quote == QUOTE_SINGLE)
    {
        printf("ERROR: syntax error: unclosed single quote\n");
        return (NULL);
    }
    else if (quote == QUOTE_DOUBLE)
    {
        printf("ERROR: syntax error: unclosed double quote\n");
        return (NULL);
    }
    end = *i;
    word = ft_substr(line, start, end - start);
    return (word);
}

char	*read_operator(char *line, int *i)
{
	int		start;
	int		len;
	char	*operator;

	start = *i;
	len = 1;

	if ((line[*i] == '<' && line[*i + 1] == '<')
		|| (line[*i] == '>' && line[*i + 1] == '>'))
		len = 2;

	operator = ft_substr(line, start, len);
	if (!operator)
		return (NULL);

	*i += len;
	return (operator);
}

static void skip_leading_delimiter(char *line, int *i)
{
    while (is_delimiter(line[*i]))
        (*i)++;
}

static void adding_token(char **token, t_token **token_lst)
{
    t_token *new_token;

    new_token = token_new(*token, classify_operator(*token));
    free(*token);
    if (!new_token)
        return ;
    token_add_back(token_lst, new_token);
}

t_token *tokenizer(char *line_read)
{
    int i;
    char *token;
    t_token *token_lst;
    
    token_lst = NULL;
    if (!line_read)
        return (NULL);
    i = 0;
    while (line_read[i])
    {
        /* skip unecessary preceding delimiter */
        skip_leading_delimiter(line_read, &i);
        /* detect operator token & detect non-operator word*/
        if (is_operator(line_read[i]))
        {
            token = read_operator(line_read, &i);
            if (!token)
                return (NULL);
            adding_token(&token, &token_lst);
        }
        else
        {
            token = read_token(line_read, &i);
            if (!token)
                return (NULL);
            adding_token(&token, &token_lst);
        }
    }
    return (token_lst);
}