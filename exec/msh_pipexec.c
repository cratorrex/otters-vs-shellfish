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
	store = malloc(sizeof(t_mpx_fd) * i);
	while (i > 0)
	{
		i--;
		store[i][0] = 0;
		store[i][1] = 1;
	}
	return (store);
}

int	msh_pipexec(t_cmd *cmd)
{
	t_mpx_fd	*store;
	//t_mpx_fd	*pipe;
	int	i;

	i = 0;
	store = mpx_traverse_pipe(cmd);
	if (mpx_traverse_left(cmd, &store) > 0)
		/*stop exec return error*/;
	if (mpx_traverse_right(cmd, &store))
	{
		
	}
	//smthn smthn send to exec and then free
	return 0;
}

//the tedium is going to kill me...
