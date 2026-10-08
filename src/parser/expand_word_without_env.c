/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word_without_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 13:28:57 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/08 13:28:59 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_word_without_env(char *str)
{
	int		i;
	int		single_quote;
	int		double_quote;
	char	*result;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (!handle_quote(str[i], &single_quote, &double_quote))
		{
			if (!append_expanded_char(&result, str[i]))
				return (NULL);
		}
		i++;
	}
	return (result);
}
