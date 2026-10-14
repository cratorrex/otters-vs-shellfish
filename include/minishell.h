/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 20:29:37 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/14 15:29:43 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
// # define _POSIX_C_SOURCE

# include "libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
//#  define __USE_POSIX	//this is for the squiggles. ONLY USE FOR TESTING
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "msh_types.h"
# include "msh_exec.h"
# include "msh_builtins.h"

char					*rl_gets(void);
void					free_line_buffer(char **line_buffer);
void					signal_checker(t_shell *shell);

int						isfound_space(char *line);
int						is_delimiter(char c);
int						is_operator(char c);
int						is_redirection(t_token_type token_type);

t_token					*token_new(char *value, t_token_type type);
void					token_add_back(t_token **lst, t_token *new);
void					token_clear(t_token **lst);

t_redir					*redir_new(t_token_type type, char *target);
void					redir_add_back(t_redir **head, t_redir *new);

t_cmd					*cmd_new(void);
void					cmd_add_back(t_cmd **head, t_cmd *new);
int						cmd_add_args(char *value, t_cmd *cmd);

t_token_type			classify_operator(char *line);

char					*read_token(char *line, int *i);
char					*read_operator(char *line, int *i);

t_token					*tokenizer(char *line_read, t_shell *shell);

int						validate_syntax(t_token *tokens);
t_cmd					*parse_token(t_token *tokens);

char					**init_env_variable(char **envp);
char					**freed_up_env(int index, char **env);
void					freed_up_existing_env(char **existing_env);
char					**add_new_variable(char **existing_env, char *new_var);
char					**remove_variable(char **existing_env, char *var);
char					**update_variable(char **existing_env, char *var);
int						get_target_variable_index(char **existing_env,\
						char *target_var);
int						search_variable(char **existing_env, char *target_var);

char					*get_env_key(char *var);
char					*get_env_value(char *name, char **envp);
char					*append_char(char *result, char c);
char					*append_string(char *result, char *str);
int						handle_quote(char c, int *single_quote,\
						int *double_quote);
int						append_expanded_char(char **result, char c);
char					*expand_tilde(char *home, int *i, char slash);
char					*expand_variable(char *str, int *i, t_shell *shell);
char					*expand_word(char *str, t_shell *shell);
char					*expand_word_without_env(char *str);
int						expand_command(t_cmd *cmd, t_shell *shell);

void					print_env(char **env);

int						init_shell(t_shell *shell, char **envp);
void					set_shell_level(t_shell *shell, char *shlvl);

void					clean_up_arr_str(char **arr);
void					clean_up_redirs(t_redir *redirs);
void					clean_up_cmd(t_cmd *cmd);
void					clean_up_shell(t_shell *shell);

int						is_empty_prompt(const char *line_read);
int						is_only_space(const char *line_read);

long					ft_atol(const char *str);

#endif
