/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 14:21:53 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/11 14:21:55 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_commands(t_cmd *cmd)
{
	size_t	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (-1);
	}
	return (0);
}

int	setup_child_pipe_fds(int prev_read_fd, int pipe_fd[2],
		int has_next)
{
	if (prev_read_fd >= 0 && dup2(prev_read_fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close_child_pipe_fds(prev_read_fd, pipe_fd);
		return (-1);
	}
	if (has_next && dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close_child_pipe_fds(prev_read_fd, pipe_fd);
		return (-1);
	}
	close_child_pipe_fds(prev_read_fd, pipe_fd);
	return (0);
}

void	close_child_pipe_fds(int prev_read_fd, int pipe_fd[2])
{
	if (prev_read_fd >= 0)
		close(prev_read_fd);
	if (pipe_fd[0] >= 0)
		close(pipe_fd[0]);
	if (pipe_fd[1] >= 0)
		close(pipe_fd[1]);
}

void	close_parent_pipe_fds(t_executor *exec, int has_next)
{
	if (exec->prev_read_fd >= 0)
		close(exec->prev_read_fd);
	exec->prev_read_fd = -1;
	if (has_next)
	{
		close(exec->pipe_fd[1]);
		exec->prev_read_fd = exec->pipe_fd[0];
	}
	else if (exec->pipe_fd[0] >= 0)
		close(exec->pipe_fd[0]);
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
}
