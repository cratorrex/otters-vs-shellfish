/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:29:49 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/08 13:30:07 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *result, char c)
{
	char	*tmp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(result, buf);
	free(result);
	return (tmp);
}

char	*append_string(char *result, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(result, str);
	free(result);
	return (tmp);
}

int	handle_quote(char c, int *single_quote, int *double_quote)
{
	if (c == '\'' && !(*double_quote))
	{
		*single_quote = !(*single_quote);
		return (1);
	}
	if (c == '"' && !(*single_quote))
	{
		*double_quote = !(*double_quote);
		return (1);
	}
	return (0);
}
