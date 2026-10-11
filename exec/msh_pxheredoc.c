/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pxheredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 18:18:31 by thtay             #+#    #+#             */
/*   Updated: 2026/09/08 18:18:34 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static volatile sig_atomic_t	g_heredoc_interrupted;

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
}

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

static char	*expand_heredoc_line(char *line, t_shell *shell)
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

static int	write_all(int fd, const char *text)
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

static int	line_matches_delimiter(char *line, const char *delimiter)
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

static int	create_heredoc_temp_fd(char **path)
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

static int	start_heredoc_signal(struct sigaction *old_action)
{
	struct sigaction	action;

	action.sa_handler = heredoc_sigint;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return (sigaction(SIGINT, &action, old_action));
}

static int	end_heredoc_signal(struct sigaction *old_action)
{
	if (sigaction(SIGINT, old_action, NULL) == -1)
	{
		perror("minishell: sigaction");
		return (-1);
	}
	return (0);
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

static char	*read_heredoc_line(void)
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

static int	store_heredoc_line(char *line, int fd, int expand_content,
		t_shell *shell)
{
	char	*content;
	char	*with_newline;
	int	status;

	content = line;
	if (expand_content)
	{
		content = expand_heredoc_line(line, shell);
		free(line);
		if (!content)
			return (-1);
	}
	with_newline = ft_strjoin(content, "\n");
	status = 0;
	if (!with_newline || write_all(fd, with_newline) == -1)
		status = -1;
	if (status == -1)
		perror("minishell: heredoc write");
	free(with_newline);
	free(content);
	return (status);
}

static int	collect_heredoc_lines(int fd, const char *delimiter,
		int expand_content, t_shell *shell)
{
	char	*line;
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		errno = 0;
		line = read_heredoc_line();
		if (g_heredoc_interrupted)
			return (free(line), shell->exit_status = 130, -1);
		if (!line)
		{
			if (errno != 0)
				return (perror("minishell: heredoc read"), -1);
			ft_putstr_fd("minishell: warning: here-document ended by EOF\n",
				STDERR_FILENO);
			return (0);
		}
		if (line_matches_delimiter(line, delimiter))
			return (free(line), 0);
		if (store_heredoc_line(line, fd, expand_content, shell) == -1)
			return (-1);
	}
}

static int	finish_heredoc_file(int fd, char *path, int failed)
{
	int	read_fd;

	if (close(fd) == -1)
	{
		perror("minishell: close");
		failed = 1;
	}
	if (failed)
	{
		if (unlink(path) == -1)
			perror("minishell: heredoc unlink");
		free(path);
		return (-1);
	}
	read_fd = open(path, O_RDONLY);
	if (read_fd == -1)
		perror("minishell: heredoc reopen");
	if (unlink(path) == -1)
		perror("minishell: heredoc unlink");
	free(path);
	return (read_fd);
}

/* Returns a readable FD at its start; the caller owns and closes it. */
int	create_heredoc_fd(const char *delimiter, int expand_content,
		t_shell *shell)
{
	char	*path;
	struct sigaction	old_action;
	int	fd;
	int	failed;

	if (!delimiter || !shell)
		return (-1);
	path = NULL;
	fd = create_heredoc_temp_fd(&path);
	if (fd == -1)
		return (perror("minishell: heredoc"), -1);
	g_heredoc_interrupted = 0;
	if (start_heredoc_signal(&old_action) == -1)
	{
		perror("minishell: sigaction");
		return (finish_heredoc_file(fd, path, 1));
	}
	failed = (collect_heredoc_lines(fd, delimiter, expand_content, shell) == -1);
	if (end_heredoc_signal(&old_action) == -1)
		failed = 1;
	return (finish_heredoc_file(fd, path, failed));
}
