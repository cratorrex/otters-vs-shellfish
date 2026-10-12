/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 17:08:43 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/11 17:08:45 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_heredoc_interrupted = 1;
	write(STDOUT_FILENO, "\n", 1);
}

int	start_heredoc_signal(struct sigaction *old_action)
{
	struct sigaction	action;

	action.sa_handler = heredoc_sigint;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return (sigaction(SIGINT, &action, old_action));
}

int	end_heredoc_signal(struct sigaction *old_action)
{
	if (sigaction(SIGINT, old_action, NULL) == -1)
	{
		perror("minishell: sigaction");
		return (-1);
	}
	return (0);
}
