/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_cleaner.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 15:54:58 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/11 15:55:12 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_child(t_cmd *cmd, t_executor *exec)
{
	clean_up_cmd(cmd);
	clean_up_shell(exec->shell);
	free(exec->pids);
}

void	close_executor_fds(t_executor *exec)
{
	if (exec->prev_read_fd >= 0)
		close(exec->prev_read_fd);
	if (exec->pipe_fd[0] >= 0)
		close(exec->pipe_fd[0]);
	if (exec->pipe_fd[1] >= 0)
		close(exec->pipe_fd[1]);
}

int	cleanup_failed_pipeline(t_executor *exec, t_shell *shell)
{
	while (exec->launched > 0)
	{
		exec->launched--;
		while (waitpid(exec->pids[exec->launched], NULL, 0) == -1
			&& errno == EINTR)
			;
	}
	free(exec->pids);
	shell->exit_status = 1;
	return (1);
}
