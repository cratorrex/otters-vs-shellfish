/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pxheredoc_helper2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 17:07:09 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/11 17:07:32 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_matches_delimiter(char *line, const char *delimiter)
{
	size_t	line_len;
	size_t	delimiter_len;

	line_len = ft_strlen(line);
	delimiter_len = ft_strlen(delimiter);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line_len--;
	return (line_len == delimiter_len
		&& ft_strncmp(line, delimiter, delimiter_len) == 0);
}

static char	*heredoc_temp_name(unsigned int counter)
{
	char	*count_text;
	char	*name;

	count_text = ft_itoa((int)counter);
	if (!count_text)
		return (NULL);
	name = ft_strjoin(".msh_heredoc_", count_text);
	free(count_text);
	return (name);
}

int	create_heredoc_temp_fd(char **path)
{
	static unsigned int	counter;
	char				*name;
	int					fd;

	while (1)
	{
		name = heredoc_temp_name(counter++);
		if (!name)
			return (-1);
		fd = open(name, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd >= 0)
			return (*path = name, fd);
		free(name);
		if (errno != EEXIST)
			return (-1);
	}
}

static int	append_read_character(char **line, size_t *length, char character)
{
	char	*grown;

	grown = realloc(*line, *length + 2);
	if (!grown)
		return (-1);
	*line = grown;
	(*line)[(*length)++] = character;
	(*line)[*length] = '\0';
	return (0);
}

char	*read_heredoc_line(void)
{
	char	*line;
	char	character;
	size_t	length;
	ssize_t	bytes;

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	length = 0;
	while (1)
	{
		bytes = read(STDIN_FILENO, &character, 1);
		if (bytes <= 0 || character == '\n')
			break ;
		if (append_read_character(&line, &length, character) == -1)
			return (free(line), NULL);
	}
	if (bytes == -1 || (bytes == 0 && length == 0))
		return (free(line), NULL);
	return (line);
}
