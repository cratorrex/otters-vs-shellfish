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
