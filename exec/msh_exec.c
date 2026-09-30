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
int	mexec_fork(t_cmd *cmd, /* t_mpx_fd *store, */ t_shell *shell)
{
	if (is_builtin_cmd(cmd->av[0]) != UNKNOWN_CMD)
		mexec_isbuiltin(cmd, shell);
	else if (ft_strchr(cmd->av[0], '/') != NULL) //relative cmd to exec
		execve(cmd->av[0], cmd->av, shell->env); //should come later
	//else if (mexec_find_path() != NULL)
	//	; //do something
	else
		return (127); //{SHELL}: command not found: {CMD}
	return (0);
}

/*thing*/
int	mexec_isbuiltin(t_cmd *cmd, t_shell *shell)
{
	long status;
	int builtin;

	status = 0;
	builtin = is_builtin_cmd(cmd->av[0]);
	if (builtin == EXIT)
		status = msh_exit(shell, cmd->av);
	else if (builtin == ENV)
		status = msh_env(shell, cmd->av);
	else if (builtin == UNSET)
		status = msh_unset(shell, cmd->av);
	else if (builtin == EXPORT)
		status = msh_export(shell, cmd->av);
	else if (builtin == PWD)
		status = msh_pwd();
	else if (builtin == CD)
		status = msh_cd(shell, cmd->av);
	else if (builtin == ECHO)
		status = msh_echo(shell, cmd->av);
	shell->exit_status = status;
	return (status);
}

//this is a stack fd[2] rn... but can be made into a heap fd[2]
int	msh_exec_one(t_cmd *cmd, t_shell *shell)
{
	t_mpx_fd	*fd;
	t_mpx_fd	dup_io;

	mpx_traverse_left(cmd, &fd);
	mpx_traverse_right(cmd, &fd);
	dup_io[0] = dup(0);
	dup_io[1] = dup(1);
	//no fork if builtin

	if (is_builtin_cmd(cmd->av[0]) != UNKNOWN_CMD)
	{
		mexec_isbuiltin(cmd, shell);
	}
	else
	{
		
	}
	return (0);
}

int	msh_exec(t_cmd *cmd, t_shell *shell)
{
	// t_mpx_fd	*store;//[0] in [1] out
	//pid_t	pid;
	// int	i;
	//char **find;

	if (!cmd->next) //basic command, no pipes
		return (msh_exec_one(cmd, shell));
	// i = 0;
	// store = msh_pipexec(cmd);//malloc and redir everythigsjkgfl
	while (cmd)
	{
		//idk fork it
/* 		if (pid < 0)
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
 */	
	}
	return (0);
}

int	execute_command(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !shell)
		return (1);
	if (!cmd->next && cmd->av && cmd->av[0]
		&& is_builtin_cmd(cmd->av[0]) != UNKNOWN_CMD)
		return (execute_single_builtin(cmd, shell));
	return (execute_pipeline(cmd, shell));
}
