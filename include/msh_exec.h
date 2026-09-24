/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 17:54:35 by thtay             #+#    #+#             */
/*   Updated: 2026/09/04 17:54:36 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef MINISHELL_H
# ifndef MSH_EXEC_H
#  define MSH_EXEC_H

typedef int	t_mpx_fd[2];
t_mpx_fd	*msh_pipexec(t_cmd *cmd);
int	msh_exec_one(t_cmd *cmd, t_shell *shell);
int	mexec_find_path(char **found, char *path, char *cmd0);


t_builtin_cmd is_builtin_cmd(char *cmd);

//if delim has quotes there should be a notice of it.
//mode1 means we expand environment
//mode0 means the delim was quoted 
int	msh_pxheredoc(char *delimiter, int mode);
t_mpx_fd	*mpx_traverse_pipe(t_cmd *cmd);
int	mpx_traverse_left(t_cmd *pass, t_mpx_fd **store);
int mpx_traverse_right(t_cmd *pass, t_mpx_fd **store);

//int	msh_exec(t_cmd *cmd, t_env *sumshi);

# endif
#endif