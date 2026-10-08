/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_token_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 10:39:05 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/08 10:39:52 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	screen_quote_status(t_quote_state *quote, const char *line, int *i)
{
	while (line[*i])
	{
		if (*quote == QUOTE_NONE)
		{
			if (line[*i] == ' ' || line[*i] == '\t' || line[*i] == '|'
				|| line[*i] == '<' || line[*i] == '>')
				break ;
			else if (line[*i] == '\'')
				*quote = QUOTE_SINGLE;
			else if (line[*i] == '"')
				*quote = QUOTE_DOUBLE;
		}
		else if (*quote == QUOTE_SINGLE)
		{
			if (line[*i] == '\'')
				*quote = QUOTE_NONE;
		}
		else if (*quote == QUOTE_DOUBLE)
		{
			if (line[*i] == '"')
				*quote = QUOTE_NONE;
		}
		(*i)++;
	}
}

char	*read_token(char *line, int *i)
{
	t_quote_state	quote;
	int				start;
	int				end;
	char			*word;

	quote = QUOTE_NONE;
	start = *i;
	screen_quote_status(&quote, line, i);
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
