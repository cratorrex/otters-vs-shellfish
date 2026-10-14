/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 14:26:34 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/12 14:29:37 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	prepare_child_execution(t_cmd *cmd, t_executor *exec, int has_next)
{
	if (setup_child_pipe_fds(exec->prev_read_fd,
			exec->pipe_fd, has_next) == -1)
	{
		cleanup_child(exec->shell->cmds, exec);
		return (-1);
	}
	if (setup_redirections(cmd->redirs, exec->shell) == -1)
	{
		cleanup_child(exec->shell->cmds, exec);
		return (-1);
	}
	if (close_prepared_heredocs(exec->shell->cmds) == -1)
		return (-1);
	return (0);
}

static void	child_execute(t_cmd *cmd, t_executor *exec, int has_next)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	if (prepare_child_execution(cmd, exec, has_next) == -1)
		exit(get_child_error_status(exec));
	if (!cmd->av || !cmd->av[0])
	{
		cleanup_child(cmd, exec);
		exit(0);
	}
	if (is_builtin_cmd(cmd->av[0]) != UNKNOWN_CMD)
	{
		status = execute_builtin(cmd, exec->shell);
		cleanup_child(exec->shell->cmds, exec);
		exit(status);
	}
	execute_external_command(cmd, exec);
	exit(1);
}

static pid_t	fork_command(t_cmd *current, t_executor *exec,
				int has_next)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (-1);
	}
	if (pid == 0)
		child_execute(current, exec, has_next);
	return (pid);
}

static int	launch_pipeline(t_cmd *cmd, t_executor *exec)
{
	t_cmd	*current;
	pid_t	pid;
	int		has_next;

	current = cmd;
	while (current)
	{
		has_next = (current->next != NULL);
		if (has_next && create_pipe(exec->pipe_fd) == -1)
			return (-1);
		pid = fork_command(current, exec, has_next);
		if (pid == -1)
			return (-1);
		exec->pids[exec->launched++] = pid;
		close_parent_pipe_fds(exec, has_next);
		current = current->next;
	}
	return (0);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	t_executor	exec;
	void		(*old_sigint)(int);

	if (init_exec(&exec, cmd, shell))
		return (1);
	old_sigint = signal(SIGINT, SIG_IGN);
	if (launch_pipeline(cmd, &exec) == -1)
	{
		close_executor_fds(&exec);
		if (old_sigint != SIG_ERR)
			signal(SIGINT, old_sigint);
		return (cleanup_failed_pipeline(&exec, shell));
	}
	close_executor_fds(&exec);
	wait_for_children(&exec, shell);
	if (old_sigint != SIG_ERR)
		signal(SIGINT, old_sigint);
	free(exec.pids);
	return (shell->exit_status);
}
