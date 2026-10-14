/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_builtins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 14:20:27 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/11 14:21:29 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->av || !cmd->av[0])
		return (0);
	return (mexec_isbuiltin(cmd, shell));
}

static int	execute_builtin_with_redirs(t_cmd *cmd, t_shell *shell)
{
	int	status;

	if (setup_redirections(cmd->redirs, shell) == -1)
	{
		if (shell->exit_status == 130)
			return (130);
		return (1);
	}
	errno = 0;
	status = execute_builtin(cmd, shell);
	return (status + (!status && errno));
}

static int	save_standard_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		perror("minishell: dup");
		if (*saved_stdin >= 0)
			close(*saved_stdin);
		if (*saved_stdout >= 0)
			close(*saved_stdout);
		return (-1);
	}
	return (0);
}

int	execute_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	if (save_standard_fds(&saved_stdin, &saved_stdout) == -1)
		return (1);
	status = execute_builtin_with_redirs(cmd, shell);
	if (restore_standard_fds(saved_stdin, saved_stdout) == -1)
		status = 1;
	shell->exit_status = status;
	return (status);
}
