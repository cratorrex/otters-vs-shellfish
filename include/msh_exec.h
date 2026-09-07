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
int	msh_pipexec(t_cmd *cmd);

//int	msh_exec(t_cmd *cmd, t_env *sumshi);

# endif
#endif