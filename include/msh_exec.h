/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exec.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 17:54:35 by thtay             #+#    #+#             */
/*   Updated: 2026/10/14 15:23:19 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef MINISHELL_H
# ifndef MSH_EXEC_H
#  define MSH_EXEC_H

typedef struct s_executor
{
	t_shell	*shell;
	int		prev_read_fd;
	int		pipe_fd[2];
	pid_t	*pids;
	size_t	cmd_count;
	size_t	launched;
}	t_executor;

void			handle_sigint(int sig);
void			setup_interactive_signals(void);
void			heredoc_sigint(int sig);
int				start_heredoc_signal(struct sigaction *old_action);
int				end_heredoc_signal(struct sigaction *old_action);

int				mexec_isbuiltin(t_cmd *cmd, t_shell *shell);
void			cleanup_child(t_cmd *cmd, t_executor *exec);
int				cleanup_failed_pipeline(t_executor *exec, t_shell *shell);
t_builtin_cmd	is_builtin_cmd(char *cmd);
size_t			count_commands(t_cmd *cmd);
int				create_pipe(int pipe_fd[2]);
int				setup_child_pipe_fds(int prev_read_fd,
					int pipe_fd[2], int has_next);
void			close_child_pipe_fds(int prev_read_fd, int pipe_fd[2]);
void			close_parent_pipe_fds(t_executor *exec, int has_next);
int				init_exec(t_executor *exec, t_cmd *cmd, t_shell *shell);
int				setup_redirections(t_redir *redirs, t_shell *shell);
int				setup_input_redirection(char *target);
int				setup_output_redirection(char *target);
int				setup_append_redirection(char *target);
int				setup_heredoc_redirection(t_redir *redir, t_shell *shell);
int				collect_command_heredocs(t_cmd *cmd, t_shell *shell);
int				close_prepared_heredocs(t_cmd *cmd);
int				restore_standard_fds(int saved_stdin, int saved_stdout);
int				execute_builtin(t_cmd *cmd, t_shell *shell);
char			*resolve_command_path(char *cmd0, char **env);
void			close_executor_fds(t_executor *exec);
void			execute_external_command(t_cmd *cmd, t_executor *exec);
int				wait_for_children(t_executor *exec, t_shell *shell);
int				execute_single_builtin(t_cmd *cmd, t_shell *shell);
int				wait_for_children(t_executor *exec, t_shell *shell);
int				get_child_error_status(t_executor *exec);
int				execute_pipeline(t_cmd *cmd, t_shell *shell);
char			*expand_heredoc_line(char *line, t_shell *shell);
int				line_matches_delimiter(char *line, const char *delimiter);
char			*read_heredoc_line(void);
int				write_all(int fd, const char *text);
int				create_heredoc_temp_fd(char **path);
int				create_heredoc_fd(const char *delimiter,
					int expand_content, t_shell *shell);
int				execute_command(t_cmd *cmd, t_shell *shell);

# endif
#endif
