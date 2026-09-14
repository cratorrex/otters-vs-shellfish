/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_redir_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 16:59:14 by thtay             #+#    #+#             */
/*   Updated: 2026/09/09 16:59:18 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//don't stop until all redirs found, but error the first file
//edgecase
//input just needs to be expanded (if heredoc unquoted)
//all sent in is already bash-compliant, ie empty word vs NULL
//\n is not accepted so that case is not handled
//within heredoc '\n' is accepted, and unclosed quotes too
/* int	mpx_traverse_left(t_cmd *pass, t_mpx_fd **store)
{
	int	err;
	int	i;

	i = 0;
	err = 0;
	while (pass != NULL)
	{
		while (pass->redirs != NULL)
		{
			if (pass->redirs->type == TOKEN_REDIR_IN && *store[i][0] >= 0)
			{
				if (*store[i][0] > 2)
					close(*store[i][0]);
				*store[i][0] = open(pass->redirs->target, O_RDONLY);
				if (*store[i][0] < 0)
					continue ;
			}
			else if (pass->redirs->type == TOKEN_HEREDOC)
			{
				if (*store[i][0] > 2)
				{
					close(*store[i][0]);
					*store[i][0] = 0;
				}
				*store[i][0] = msh_pxheredoc(pass->redirs->target, 0);
				//something something get_next_line
			}
			pass->redirs = pass->redirs->next;
		}
		pass = pass->next;
	}
	return (*store[i][0]);
} */

static int	mpx_ret_redirin(t_redir *redir, int *fd, int *err)
{
	if (redir->type == TOKEN_REDIR_IN && *fd >= 0 && *err == 0)
	{
		if (*fd > 2)
			close(*fd);
		*fd = open(redir->target, O_RDONLY);
		printf("fdin: %i\n", *fd);
		if (*fd < 0)
		{
			*err = errno;
			return (0);
		}
		return (1);
	}
	return (0);
}

static void	mpx_ret_redirhd(t_redir *redir, int *fd, int *err)
{
	int	tempfd;

	if (redir->type == TOKEN_HEREDOC || redir->type == 6)
	{
		if (*fd > 2)
			close(*fd);
		if (*fd < 0)
		{
			tempfd = msh_pxheredoc(redir->target/* , redir->type - 5 */);
			if (tempfd > 2)
				close(tempfd);
		}
		else
		{
			*fd = msh_pxheredoc(redir->target/* , redir->type - 5 */);
			printf("fdhd: %i\n", *fd);
			if (*fd < 0)
				*err = errno;
		}
	}
}

int	mpx_traverse_left(t_cmd *pass, t_mpx_fd **store)
{
	int	i;
	int	err;
	t_redir	*redir;
	
	i = 0;
	err = 0;
	while (pass != NULL)
	{
		redir = pass->redirs;
		while (redir != NULL)
		{
			if (mpx_ret_redirin(redir, &(*store[i][0]), &err))
			{
				printf("fdretin: %i\n", *store[i][0]);
			}
			else
				mpx_ret_redirhd(redir, &(*store[i][0]), &err);
			redir = redir->next;
		}
		pass = pass->next;
		i++;
	}
	return (err);
}

//fix this for errors and 