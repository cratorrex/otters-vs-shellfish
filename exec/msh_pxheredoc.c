/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pxheredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 18:18:31 by thtay             #+#    #+#             */
/*   Updated: 2026/10/11 17:06:20 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	store_heredoc_line(char *line, int fd, int expand_content,
		t_shell *shell)
{
	char	*content;
	char	*with_newline;
	int		status;

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
		if (g_signal_interrupt)
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
int	create_heredoc_fd(const char *delimiter, int expand_content, t_shell *shell)
{
	char				*path;
	struct sigaction	old_action;
	int					fd;
	int					failed;

	if (!delimiter || !shell)
		return (-1);
	path = NULL;
	fd = create_heredoc_temp_fd(&path);
	if (fd == -1)
		return (perror("minishell: heredoc"), -1);
	g_signal_interrupt = 0;
	if (start_heredoc_signal(&old_action) == -1)
	{
		perror("minishell: sigaction");
		return (finish_heredoc_file(fd, path, 1));
	}
	failed = (collect_heredoc_lines(fd, delimiter, expand_content, shell)
			== -1);
	if (end_heredoc_signal(&old_action) == -1)
		failed = 1;
	return (finish_heredoc_file(fd, path, failed));
}
