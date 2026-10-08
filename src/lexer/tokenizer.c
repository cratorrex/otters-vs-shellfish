/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <jatansil@42mail.sutd.edu.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:17:38 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/01 16:39:29 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_leading_delimiter(char *line, int *i)
{
	while (is_delimiter(line[*i]))
		(*i)++;
}

static void	adding_token(char **token, t_token **token_lst)
{
	t_token	*new_token;

	new_token = token_new(*token, classify_operator(*token));
	free(*token);
	if (!new_token)
		return ;
	token_add_back(token_lst, new_token);
}

t_token	*tokenizer(char *line_read)
{
	int		i;
	char	*token;
	t_token	*token_lst;

	token_lst = NULL;
	if (!line_read)
		return (NULL);
	i = 0;
	while (line_read[i])
	{
		skip_leading_delimiter(line_read, &i);
		if (is_operator(line_read[i]))
			token = read_operator(line_read, &i);
		else
			token = read_token(line_read, &i);
		if (!token)
		{
			token_clear(&token_lst);
			return (NULL);
		}
		adding_token(&token, &token_lst);
	}
	return (token_lst);
}
