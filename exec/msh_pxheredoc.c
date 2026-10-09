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

extern int	rl_done;
extern int	rl_catch_signals;

static volatile sig_atomic_t	g_heredoc_interrupted;

static void	heredoc_sigint(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	rl_done = 1;
	write(STDOUT_FILENO, "\n", 1);
}

static char	*append_text(char *result, const char *text)
{
	char	*joined;

	joined = ft_strjoin(result, text);
	free(result);
	return (joined);
}

static char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*result;
	char	*expanded;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			expanded = expand_variable(line, &i, shell);
			if (!expanded)
				return (free(result), NULL);
			result = append_text(result, expanded);
			free(expanded);
		}
		else
		{
			expanded = ft_substr(line, i, 1);
			if (!expanded)
				return (free(result), NULL);
			result = append_text(result, expanded);
			free(expanded);
			i++;
		}
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

static int	create_heredoc_temp_fd(char **path)
{
	static unsigned int	counter;
	char				*count_text;
	char				*name;
	int					fd;

	while (1)
	{
		count_text = ft_itoa((int)counter++);
		if (!count_text)
			return (-1);
		name = ft_strjoin(".msh_heredoc_", count_text);
		free(count_text);
		if (!name)
			return (-1);
		fd = open(name, O_CREAT | O_EXCL | O_WRONLY, 0600);
		if (fd >= 0)
		{
			*path = name;
			return (fd);
		}
		free(name);
		if (errno != EEXIST)
			return (-1);
	}
}

/*
 * Returns a readable FD positioned at the start, or -1 on failure.
 * expand_content is 0 when the delimiter was quoted, 1 otherwise.
 * The caller owns the returned FD and must close it after dup2().
 */
int	create_heredoc_fd(const char *delimiter, int expand_content,
		t_shell *shell)
{
	char	*line;
	char	*content;
	char	*line_with_newline;
	char	*path;
	void	(*old_sigint)(int);
	int		old_catch_signals;
	int		fd;
	int		read_fd;

	if (!delimiter || !shell)
		return (-1);
	path = NULL;
	fd = create_heredoc_temp_fd(&path);
	if (fd == -1)
		return (perror("minishell: heredoc"), -1);
	g_heredoc_interrupted = 0;
	old_catch_signals = rl_catch_signals;
	rl_catch_signals = 0;
	old_sigint = signal(SIGINT, heredoc_sigint);
	while (1)
	{
		line = readline("");
		if (g_heredoc_interrupted)
		{
			free(line);
			close(fd);
			unlink(path);
			free(path);
			if (old_sigint != SIG_ERR)
				signal(SIGINT, old_sigint);
			rl_catch_signals = old_catch_signals;
			shell->exit_status = 130;
			return (-1);
		}
		if (!line)
		{
			ft_putstr_fd("minishell: warning: here-document ended by EOF\n",
				STDERR_FILENO);
			break ;
		}
		if (line_matches_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		content = line;
		if (expand_content)
		{
			content = expand_heredoc_line(line, shell);
			free(line);
			if (!content)
			{
				close(fd);
				unlink(path);
				free(path);
				if (old_sigint != SIG_ERR)
					signal(SIGINT, old_sigint);
				rl_catch_signals = old_catch_signals;
				return (-1);
			}
		}
		line_with_newline = ft_strjoin(content, "\n");
		if (!line_with_newline || write_all(fd, line_with_newline) == -1)
		{
			perror("minishell: heredoc write");
			free(line_with_newline);
			free(content);
			close(fd);
			unlink(path);
			free(path);
			if (old_sigint != SIG_ERR)
				signal(SIGINT, old_sigint);
			rl_catch_signals = old_catch_signals;
			return (-1);
		}
		free(line_with_newline);
		free(content);
	}
	if (old_sigint != SIG_ERR)
		signal(SIGINT, old_sigint);
	rl_catch_signals = old_catch_signals;
	close(fd);
	read_fd = open(path, O_RDONLY);
	if (read_fd == -1)
		perror("minishell: heredoc reopen");
	if (unlink(path) == -1 && read_fd >= 0)
		perror("minishell: heredoc unlink");
	free(path);
	return (read_fd);
}
