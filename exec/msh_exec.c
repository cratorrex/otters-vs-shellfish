/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 18:10:44 by thtay             #+#    #+#             */
/*   Updated: 2026/09/02 22:05:03 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mexec_isbuiltin(t_cmd *cmd, t_shell *shell)
{
	long	status;
	int		builtin;

	status = 0;
	builtin = is_builtin_cmd(cmd->av[0]);
	if (builtin == EXIT)
		status = msh_exit(shell, cmd->av);
	else if (builtin == ENV)
		status = msh_env(shell, cmd->av);
	else if (builtin == UNSET)
		status = msh_unset(shell, cmd->av);
	else if (builtin == EXPORT)
		status = msh_export(shell, cmd->av);
	else if (builtin == PWD)
		status = msh_pwd();
	else if (builtin == CD)
		status = msh_cd(shell, cmd->av);
	else if (builtin == ECHO)
		status = msh_echo(shell, cmd->av);
	shell->exit_status = status;
	return (status);
}

int	init_exec(t_executor *exec, t_cmd *cmd, t_shell *shell)
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

void	execute_external_command(t_cmd *cmd, t_executor *exec)
{
	char	*path;
	int		status;

	path = resolve_command_path(cmd->av[0], exec->shell->env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->av[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		cleanup_child(exec->shell->cmds, exec);
		exit(127);
	}
	execve(path, cmd->av, exec->shell->env);
	perror(cmd->av[0]);
	status = 126;
	if (errno == ENOENT)
		status = 127;
	free(path);
	cleanup_child(exec->shell->cmds, exec);
	exit(status);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !shell)
		return (1);
	shell->cmds = cmd;
	if (!cmd->next && cmd->av && cmd->av[0]
		&& is_builtin_cmd(cmd->av[0]) != UNKNOWN_CMD)
		return (execute_single_builtin(cmd, shell));
	return (execute_pipeline(cmd, shell));
}
