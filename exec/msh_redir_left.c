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

// int sto_store = dup(0);
// dup2(*fd, 0);
// close(*fd);
//
// char te[2] = "";
// int re = read(0, te, 1);
// while (re)
// 	{printf("%s", te); re = read(0, te, 1);}
// printf("%i\n", re);
// dup2(sto_store, 0);
static void	mpx_ret_redirhd(t_redir *redir, int *fd, int *err)
{
	int	tempfd;

	if (redir->type == TOKEN_HEREDOC || redir->type == TOKEN_HEREDOC_QUOTED)
	{
		if (*fd > 2)
		{
			close(*fd);
			*fd = 1;
		}
		tempfd = msh_pxheredoc(redir->target, redir->type - 5);
		printf("fdhd: %i\n", tempfd);
		if (tempfd < 0 && *err == 0)
			*err = errno;
		if (*fd < 0 && tempfd > 2)
			close(tempfd);
		else
			*fd = tempfd;
	}
}

/*
write(1, thing, size);
write(pfd[1], thing, size);
*/
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
				printf("fdretin: %i\n", *store[i][0]);
			else
				mpx_ret_redirhd(redir, &(*store[i][0]), &err);
			redir = redir->next;
		}
		pass = pass->next;
		i++;
	}
	return (err);
}
