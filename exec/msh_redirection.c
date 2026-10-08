#include "minishell.h"

int	setup_input_redirection(char *target)
{
	int	fd;

	fd = open(target, O_RDONLY);
	if (fd == -1)
	{
		perror(target);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_output_redirection(char *target)
{
	int	fd;

	fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror(target);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_append_redirection(char *target)
{
	int	fd;

	fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		perror(target);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_heredoc_redirection(t_redir *redir, t_shell *shell)
{
	int	fd;

	/*
	 * This call assumes msh_pxheredoc() has been refactored to accept
	 * t_shell * and to return a readable FD, or -1 on failure.
	 */
	fd = create_heredoc_fd(redir->target,
			redir->type == TOKEN_HEREDOC_QUOTED, shell);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	setup_redirections(t_redir *redirs, t_shell *shell)
{
	while (redirs)
	{
		if (redirs->type == TOKEN_REDIR_IN
			&& setup_input_redirection(redirs->target) == -1)
			return (-1);
		else if (redirs->type == TOKEN_REDIR_OUT
			&& setup_output_redirection(redirs->target) == -1)
			return (-1);
		else if (redirs->type == TOKEN_APPEND
			&& setup_append_redirection(redirs->target) == -1)
			return (-1);
		else if ((redirs->type == TOKEN_HEREDOC
				|| redirs->type == TOKEN_HEREDOC_QUOTED)
			&& setup_heredoc_redirection(redirs, shell) == -1)
			return (-1);
		redirs = redirs->next;
	}
	return (0);
}

int	restore_standard_fds(int saved_stdin, int saved_stdout)
{
	int	failed;

	failed = 0;
	if (saved_stdin >= 0)
	{
		if (dup2(saved_stdin, STDIN_FILENO) == -1)
		{
			perror("minishell: restore stdin");
			failed = 1;
		}
		close(saved_stdin);
	}
	if (saved_stdout >= 0)
	{
		if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		{
			perror("minishell: restore stdout");
			failed = 1;
		}
		close(saved_stdout);
	}
	return (failed ? -1 : 0);
}
