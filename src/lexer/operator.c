/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <jatansil@42mail.sutd.edu.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:14:30 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/01 16:15:24 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	classify_operator(char *line)
{
	int	i;

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
