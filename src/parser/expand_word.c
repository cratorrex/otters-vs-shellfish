/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <jatansil@42mail.sutd.edu.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 17:04:39 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/01 17:08:20 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_variable(char *str, int *i, char *result, t_shell *shell)
{
	char	*expanded;

	expanded = expand_variable(str, i, shell);
	if (!expanded)
	{
		free(result);
		return (NULL);
	}
	result = append_string(result, expanded);
	free(expanded);
	return (result);
}

int	append_expanded_char(char **result, char c)
{
	*result = append_char(*result, c);
	if (!*result)
		return (0);
	return (1);
}

static char	*process_expand_char(char *str, int *i, char *result,
		t_shell *shell)
{
	if (str[*i] == '$')
		return (handle_variable(str, i, result, shell));
	result = append_char(result, str[*i]);
	(*i)++;
	return (result);
}

static char	*process_expand_loop(char *str, t_shell *shell, int *i,
		char *result)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (str[*i])
	{
		if (handle_quote(str[*i], &single_quote, &double_quote))
			(*i)++;
		else if (str[*i] == '$' && !single_quote)
			result = process_expand_char(str, i, result, shell);
		else
		{
			result = append_char(result, str[*i]);
			(*i)++;
		}
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*expand_word(char *str, t_shell *shell)
{
	int		i;
	char	*result;

	i = 0;
	if (*str == '~' && str[1] != '\"' && str[1] != '\'')
		result = expand_tilde(get_env_value("HOME", shell->env), &i, str[1]);
	else
		result = ft_strdup("");
	if (!result)
		return (NULL);
	return (process_expand_loop(str, shell, &i, result));
}
