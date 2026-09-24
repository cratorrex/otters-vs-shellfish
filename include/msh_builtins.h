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

#include "minishell.h"

int	msh_echo(int count, char **string);
int	msh_pwd(int count, char **string);
int	msh_cd(t_shell *shell, char **av);
int	msh_export(t_shell *shell, char **av);
int msh_env(t_shell *shell);
int msh_unset(t_shell *shell, char **av);

int	cd_set_variable(t_shell *shell, char *key, char *value);
int	cd_update_env(t_shell *shell, char *oldpwd, char *newpwd);
int	cd_change_dir(t_shell *shell, char *path, int print_path);
void free_env(char **env);
int	print_export(char **env);

# endif
#endif
