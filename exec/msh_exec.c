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

//env assumes a created env struct

int	mexec_fork()
{
	
}

/*thing*/
int	mexec_isbuiltin()
{

}

int	msh_exec_one(t_cmd *cmd/* , t_env env */)
{
	t_mpx_fd	fd;

	mpx_traverse_left(cmd, &fd);
	mpx_traverse_right(cmd, &fd);
	//no fork if builtin
}

int	msh_exec(t_cmd *cmd/* , t_env *envp */)
{
	//t_mpx_fd	*pipe;//malloc and pipe // this is alr done... oml
	t_mpx_fd	*store;
	pid_t	last;
	int	i;

	if (!cmd->next) //basic command, no pipes
		return (msh_exec_one(cmd, envp));
	i = 0;
	store = msh_pipexec(cmd);//malloc and redir everythigsjkgfl
	while (cmd)
	{
		//idk fork it
		if (pid < 0)
			cry();//update last to indicate error
		else if (!pid)
		{
			set_fd(fd, pfd);
			gra_elsewhere();
		}
		else
			last = sumshit;
		//rmb fork errors
		return (child_wait());
	}
}
