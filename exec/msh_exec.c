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
//? what do here idrky,bws
int	mexec_fork()
{
	
}

/*thing*/
int	mexec_isbuiltin(t_mpx_fd *store, int bi, t_cmd *cmd, t_shell *shell)
{
	if (is_builtin_cmd(cmd->av[0]) == EXIT)
		return (msh_exit());
	if (is_builtin_cmd(cmd->av[0]) == ENV)
		return (msh_env());
	if (is_builtin_cmd(cmd->av[0]) == UNSET)
		return (msh_unset());
	if (is_builtin_cmd(cmd->av[0]) == EXPORT)
		return (msh_export());
	if (is_builtin_cmd(cmd->av[0]) == PWD)
		return (msh_pwd());
	if (is_builtin_cmd(cmd->av[0]) == CD)
		return (msh_cd(shell, cmd->av));
	if (is_builtin_cmd(cmd->av[0]) == ECHO)
		return (msh_echo());
}

//this is a stack fd[2] rn... but can be made into a heap fd[2]
int	msh_exec_one(t_cmd *cmd, t_shell *shell)
{
	t_mpx_fd	fd;

	mpx_traverse_left(cmd, &fd);
	mpx_traverse_right(cmd, &fd);
	//no fork if builtin

	if (is_builtin_cmd(cmd->av[0]))
}

int	msh_exec(t_cmd *cmd, t_shell *shell)
{
	//t_mpx_fd	*pipe;//malloc and pipe // this is alr done... oml
	t_mpx_fd	*store;//[0] in [1] out
	pid_t	pid;
	int	i;

	if (!cmd->next) //basic command, no pipes
		return (msh_exec_one(cmd, shell));
	i = 0;
	store = msh_pipexec(cmd);//malloc and redir everythigsjkgfl
	while (cmd)
	{
		if (is_builtin_cmd(cmd->av[0]) != UNKNOWN_CMD)
			mexec_isbuiltin();
		//idk fork it
		if (pid < 0)
			cry();//update last to indicate error
		else if (!pid)
		{
			set_fd(fd, pfd);
			gra_elsewhere();
		}
		else
			pid = sumshit;
		//rmb fork errors
		return (child_wait());
	}
}
