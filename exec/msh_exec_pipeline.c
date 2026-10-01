#include "minishell.h"

int	decode_wait_status(int wait_status)
{
	if (WIFEXITED(wait_status))
		return (WEXITSTATUS(wait_status));
	if (WIFSIGNALED(wait_status))
		return (128 + WTERMSIG(wait_status));
	return (1);
}

int	wait_for_children(t_executor *exec, t_shell *shell)
{
	size_t	i;
	int		wait_status;
	int		last_status;
	pid_t	result;

	i = 0;
	last_status = 1;
	while (i < exec->launched)
	{
		while (1)
		{
			result = waitpid(exec->pids[i], &wait_status, 0);
			if (result == -1 && errno == EINTR)
				continue ;
			break ;
		}
		if (result == -1)
		{
			perror("minishell: waitpid");
			last_status = 1;
		}
		else if (i == exec->cmd_count - 1)
			last_status = decode_wait_status(wait_status);
		i++;
	}
	shell->exit_status = last_status;
	return (last_status);
}

void	child_execute(t_cmd *cmd, t_shell *shell, int prev_read_fd,
		int pipe_fd[2], int has_next)
{
	if (setup_child_pipe_fds(prev_read_fd, pipe_fd, has_next) == -1)
		exit(1);
	/*
	 * Redirections follow pipe setup so an explicit input/output redirect
	 * overrides that command's corresponding pipeline connection.
	 */
	if (setup_redirections(cmd->redirs, shell) == -1)
		exit(1);
	if (!cmd->av || !cmd->av[0])
		exit(0);
	if (is_builtin_cmd(cmd->av[0]) != UNKNOWN_CMD)
		exit(execute_builtin(cmd, shell));
	execute_external_command(cmd, shell);
	exit(1);
}

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	t_executor	exec;
	t_cmd		*current;
	pid_t		pid;
	int			has_next;

	exec.cmd_count = count_commands(cmd);
	exec.pids = malloc(sizeof(pid_t) * exec.cmd_count);
	if (!exec.pids)
		return (perror("minishell: malloc"), shell->exit_status = 1, 1);
	exec.prev_read_fd = -1;
	exec.pipe_fd[0] = -1;
	exec.pipe_fd[1] = -1;
	exec.launched = 0;
	current = cmd;
	while (current)
	{
		has_next = (current->next != NULL);
		if (has_next && create_pipe(exec.pipe_fd) == -1)
			break ;
		pid = fork();
		if (pid == -1)
		{
			perror("minishell: fork");
			break ;
		}
		if (pid == 0)
			child_execute(current, shell, exec.prev_read_fd,
				exec.pipe_fd, has_next);
		exec.pids[exec.launched++] = pid;
		close_parent_pipe_fds(&exec, has_next);
		current = current->next;
	}
	if (exec.prev_read_fd >= 0)
		close(exec.prev_read_fd);
	if (exec.pipe_fd[0] >= 0)
		close(exec.pipe_fd[0]);
	if (exec.pipe_fd[1] >= 0)
		close(exec.pipe_fd[1]);
	if (current)
	{
		/*
		 * A pipe or fork failed before all commands launched.
		 * Reap launched children, then report the launch failure.
		 */
		while (exec.launched > 0)
		{
			exec.launched--;
			while (waitpid(exec.pids[exec.launched], NULL, 0) == -1
				&& errno == EINTR)
				;
		}
		free(exec.pids);
		shell->exit_status = 1;
		return (1);
	}
	wait_for_children(&exec, shell);
	free(exec.pids);
	return (shell->exit_status);
}