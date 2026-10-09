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

static int	check_token_empty_envs(char *value, t_shell *shell)
{
	int		i;
	char	*var;

	i = 0;
	while (value[i])
	{
		var = expand_variable(value, &i, shell);
		if (var[0] != 0)
			return (free(var), 0);
		free (var);
	}
	return (1);
}

static void	skip_leading_delimiter(char *line, int *i)
{
	while (is_delimiter(line[*i]))
		(*i)++;
}

static void	adding_token(char **token, t_token **token_lst, t_shell *shell)
{
	t_token	*new_token;

	new_token = token_new(*token, classify_operator(*token));
	free(*token);
	if (!new_token)
		return ;
	if (new_token->type == TOKEN_WORD && new_token->value[0] == '$'
		&& !(ft_strchr(new_token->value, '"')
			|| ft_strchr(new_token->value, '\''))
		&& check_token_empty_envs(new_token->value, shell))
	{
		free (new_token->value);
		free (new_token);
		shell->exit_status = 1;
		return ;
	}
	token_add_back(token_lst, new_token);
}

t_token	*tokenizer(char *line_read, t_shell *shell)
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
			return (token_clear(&token_lst), NULL);
		adding_token(&token, &token_lst, shell);
	}
	return (token_lst);
}
