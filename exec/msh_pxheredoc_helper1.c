/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pxheredoc_helper1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 17:06:32 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/11 17:06:42 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_text(char *result, const char *text)
{
	char	*joined;

	joined = ft_strjoin(result, text);
	free(result);
	return (joined);
}

static char	*append_expanded_variable(char *result, char *line, int *i,
		t_shell *shell)
{
	char	*expanded;

	expanded = expand_variable(line, i, shell);
	if (!expanded)
		return (free(result), NULL);
	result = append_text(result, expanded);
	free(expanded);
	return (result);
}

static char	*append_heredoc_char(char *result, char *line, int *i)
{
	char	*character;

	character = ft_substr(line, *i, 1);
	if (!character)
		return (free(result), NULL);
	result = append_text(result, character);
	free(character);
	(*i)++;
	return (result);
}

char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			result = append_expanded_variable(result, line, &i, shell);
		else
			result = append_heredoc_char(result, line, &i);
		if (!result)
			return (NULL);
	}
	return (result);
}

int	write_all(int fd, const char *text)
{
	size_t	offset;
	size_t	len;
	ssize_t	written;

	offset = 0;
	len = ft_strlen(text);
	while (offset < len)
	{
		written = write(fd, text + offset, len - offset);
		if (written < 0)
			return (-1);
		offset += (size_t)written;
	}
	return (0);
}
