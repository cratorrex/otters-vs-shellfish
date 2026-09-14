/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:59:24 by thtay             #+#    #+#             */
/*   Updated: 2026/09/09 16:59:25 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//stop early if file cannot be accessed
int	mpx_traverse_right(t_cmd *pass, t_mpx_fd **store)
{
	int	i;
	t_redir	*redir;

	i = 0;
	while (pass != NULL)
	{
		redir = pass->redirs;
		while (redir != NULL)
		{
			if (redir->type == 3 || redir->type == 4)
			{
				if (*store[i][1] > 2)
					close(*store[i][1]);
				if (redir->type == TOKEN_REDIR_OUT)
					*store[i][1] = open(redir->target, O_CREAT | O_TRUNC, 0777);
				else if (redir->type == TOKEN_APPEND)
					*store[i][1] = open(redir->target, O_CREAT | O_APPEND, 0777);
				printf("fdout: %i\n", *store[i][1]);
			}
			if ((*store)[i][1] < 0)
				return (errno);
			redir = redir->next;
			
		}
		pass = pass->next;
		i++;
	}
	return (0);
}
