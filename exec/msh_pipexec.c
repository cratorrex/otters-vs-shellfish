/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pipexec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 18:23:53 by thtay             #+#    #+#             */
/*   Updated: 2026/09/02 18:23:54 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*assuming pipes and redirections
//just as an in case
//
//pass1
//traverse the linked list for left redirect
//discard "result" on next redirect
//
//result collected, now do pass 2
//
//traverse the linked list for right redirect
//close file on next redirect, open the next one
//
//exec
//then get_next_pipe*/



// CLOSE THE FDs BEFORE OPENING A NEW ONE
// CLOSE THE FDs BEFORE OPENING A NEW ONE
// CLOSE THE FDs BEFORE OPENING A NEW ONE


//don't stop until all redirs found, but error the first file
int	mpx_traverse_left(t_cmd *pass, int count)
{
	int	ret_fd;

	ret_fd = 0;
	while (pass != NULL)
	{
		while (pass->redirs != NULL)
		{
			if (pass->redirs->type == TOKEN_REDIR_IN && ret_fd >= 0)
			{
				if (ret_fd > 2)
					close(ret_fd);
				ret_fd = open(pass->redirs->target, O_RDONLY);
				if (ret_fd < 0)
					continue ;
				// dup2(ret_fd, 0);
				//dup to fd0 later...
			}
			else if (pass->redirs->type == TOKEN_HEREDOC)//edgecase\
			input just needs to be expanded (if heredoc unquoted)\
			all sent in is already bash-compliant, ie empty word vs NULL\
			\n is not accepted so that case is not handled\
			within heredoc '\n' is accepted, and unclosed quotes too
			{
				if (ret_fd > 2)
				{
					close(ret_fd);
					ret_fd = 0;
				}
				msh_pxheredoc();
				/* something something get_next_line */
			}
			pass->redirs = pass->redirs->next;
		}
		pass = pass->next;
	}

}

//stop early if file cannot be accessed
int	mpx_traverse_right(t_cmd *pass, int count)
{
	int	ret_fd;

	ret_fd = 1;
	while (pass != NULL)
	{
		while (pass->redirs != NULL)
		{
			if (pass->redirs->type == TOKEN_REDIR_OUT)
			{
				if(ret_fd > 2)
					close(ret_fd);
				ret_fd = open(pass->redirs->target, O_TRUNC);
			}
			else if (pass->redirs->type == TOKEN_APPEND)
			{
				if(ret_fd > 2)
					close(ret_fd);
				ret_fd = open(pass->redirs->target, O_APPEND);
			}
			if (ret_fd < 0)
				return (ret_fd);
			pass->redirs = pass->redirs->next;
		}
		pass = pass->next;
	}
	return (ret_fd);
}

//mallocs a fd storage that will be passed to pipes
t_mpx_fd	*mpx_traverse_pipe(t_cmd *cmd)
{
	int	i;
	t_mpx_fd *store;

	i = 0;
	while (cmd)
	{
		i ++;
		cmd = cmd->next;
	}
	store = malloc(sizeof(t_mpx_fd) * i + 1);
	return (store);
}

int	msh_pipexec(t_cmd *cmd)
{
	t_mpx_fd	*store;
	t_mpx_fd	*pipe;
	int	i;

	store = mpx_traverse_pipe(cmd);
	store = mpx_traverse_left(cmd, i);
	if (store[i][0] < 0)//move this outside... we parse all\
	redirs first before doing err_exec
	{} //stop here, give an error
	store = mpx_traverse_right(cmd, i);
	if (store[i][1] < 0) //exit
	{}
	//smthn smthn send to exec and then free
}

//the tedium is going to kill me...
