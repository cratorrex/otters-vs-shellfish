/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redirection_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 17:08:22 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/11 17:08:31 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_heredoc_redirection(t_redir *redir, t_shell *shell)
{
	(void)shell;
	if (redir->heredoc_fd < 0)
		return (-1);
	if (dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		return (-1);
	}
	if (close(redir->heredoc_fd) == -1)
	{
		perror("minishell: close");
		redir->heredoc_fd = -1;
		return (-1);
	}
	redir->heredoc_fd = -1;
	return (0);
}

static int	prepare_heredoc(t_redir *redir, t_shell *shell)
{
	redir->heredoc_fd = create_heredoc_fd(redir->target,
			redir->type == TOKEN_HEREDOC, shell);
	if (redir->heredoc_fd < 0)
		return (-1);
	return (0);
}

int	close_prepared_heredocs(t_cmd *cmd)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->heredoc_fd >= 0)
			{
				if (close(redir->heredoc_fd) == -1)
					return (perror("minishell: close heredoc"), -1);
				redir->heredoc_fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

static int	collect_redir_heredocs(t_redir *redir, t_shell *shell)
{
	while (redir)
	{
		if ((redir->type == TOKEN_HEREDOC
				|| redir->type == TOKEN_HEREDOC_QUOTED)
			&& prepare_heredoc(redir, shell) == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

int	collect_command_heredocs(t_cmd *cmd, t_shell *shell)
{
	while (cmd)
	{
		if (collect_redir_heredocs(cmd->redirs, shell) == -1)
			return (-1);
		cmd = cmd->next;
	}
	return (0);
}
