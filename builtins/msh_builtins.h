/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtins.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 16:58:22 by thtay             #+#    #+#             */
/*   Updated: 2026/08/14 16:58:24 by thtay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef MINISHELL_H
# ifndef MSH_BUILTINS_H
#  define MSH_BUILTINS_H

int	msh_echo(int count, char **string);
int	msh_pwd(char **string);

# endif
#endif
