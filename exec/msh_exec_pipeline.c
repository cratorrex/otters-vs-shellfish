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

void	child_execute(t_cmd *cmd, t_executor *exec, int has_next)
{
	int status;

	if (setup_child_pipe_fds(exec->prev_read_fd, exec->pipe_fd, has_next) == -1)
		exit(1);
	if (setup_redirections(cmd->redirs, exec->shell) == -1)
		exit(1);
	if (!cmd->av || !cmd->av[0])
		exit(0);
	if (is_builtin_cmd(cmd->av[0]) != UNKNOWN_CMD)
	{
		status = execute_builtin(cmd, exec->shell);
		cleanup_child(exec->shell->cmds, exec);
		exit(status);
	}
	execute_external_command(cmd, exec);
	exit(1);
}

static int	cleanup_failed_pipeline(t_executor *exec, t_shell *shell)
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


static int	init_exec(t_executor *exec, t_cmd *cmd, t_shell *shell)
{
	exec->cmd_count = count_commands(cmd);
	exec->pids = malloc(sizeof(pid_t) * exec->cmd_count);
	if (!exec->pids)
	{
		perror("minishell: malloc");
		shell->exit_status = 1;
		return (1);
	}
	exec->prev_read_fd = -1;
	exec->pipe_fd[0] = -1;
	exec->pipe_fd[1] = -1;
	exec->launched = 0;
	exec->shell = shell;
	return (0);
}

static pid_t	fork_command(t_cmd *current,t_executor *exec,
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

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	t_executor	exec;
	t_cmd		*current;
	pid_t		pid;
	int			has_next;

	if (init_exec(&exec, cmd, shell))
		return (1);
	current = cmd;
	while (current)
	{
		has_next = (current->next != NULL);
		if (has_next && create_pipe(exec.pipe_fd) == -1)
			break ;
		pid = fork_command(current, &exec, has_next);
		if (pid == -1)
			break ;
		exec.pids[exec.launched++] = pid;
		close_parent_pipe_fds(&exec, has_next);
		current = current->next;
	}
	close_executor_fds(&exec);
	if (current)
		return (cleanup_failed_pipeline(&exec, shell));
	wait_for_children(&exec, shell);
	free(exec.pids);
	return (shell->exit_status);
}