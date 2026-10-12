/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec_pipeline_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 15:50:51 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/12 15:50:53 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	decode_wait_status(int wait_status)
{
	if (WIFEXITED(wait_status))
		return (WEXITSTATUS(wait_status));
	if (WIFSIGNALED(wait_status))
		return (128 + WTERMSIG(wait_status));
	return (1);
}

static void	report_quit_status(int wait_status)
{
	if (!WIFSIGNALED(wait_status) || WTERMSIG(wait_status) != SIGQUIT)
		return ;
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
}

static int	wait_for_child(t_executor *exec, size_t i, int *last_status)
{
	int		wait_status;
	pid_t	result;

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
		return (-1);
	}
	report_quit_status(wait_status);
	if (i == exec->cmd_count - 1)
		*last_status = decode_wait_status(wait_status);
	return (0);
}

int	wait_for_children(t_executor *exec, t_shell *shell)
{
	size_t	i;
	int		last_status;

	i = 0;
	last_status = 1;
	while (i < exec->launched)
	{
		if (wait_for_child(exec, i, &last_status) == -1)
			last_status = 1;
		i++;
	}
	shell->exit_status = last_status;
	return (last_status);
}

int	get_child_error_status(t_executor *exec)
{
	if (exec->shell->exit_status == 130)
		return (130);
	return (1);
}
