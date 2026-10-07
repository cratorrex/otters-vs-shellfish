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

typedef struct s_executor
{
	t_shell *shell;
	int		prev_read_fd;
	int		pipe_fd[2];
	pid_t	*pids;
	size_t	cmd_count;
	size_t	launched;
}	t_executor;

int	mexec_isbuiltin(t_cmd *cmd, t_shell *shell);
t_builtin_cmd is_builtin_cmd(char *cmd);
size_t	count_commands(t_cmd *cmd);
int		create_pipe(int pipe_fd[2]);
int		setup_child_pipe_fds(int prev_read_fd, int pipe_fd[2], int has_next);
void		close_child_pipe_fds(int prev_read_fd, int pipe_fd[2]);
void		close_parent_pipe_fds(t_executor *exec, int has_next);
int		setup_redirections(t_redir *redirs, t_shell *shell);
int		setup_input_redirection(char *target);
int		setup_output_redirection(char *target);
int		setup_append_redirection(char *target);
int		setup_heredoc_redirection(t_redir *redir, t_shell *shell);
int		restore_standard_fds(int saved_stdin, int saved_stdout);
int		execute_builtin(t_cmd *cmd, t_shell *shell);
char		*resolve_command_path(char *cmd0, char **env);
void	close_executor_fds(t_executor *exec);
void		execute_external_command(t_cmd *cmd, t_executor *exec);
int		wait_for_children(t_executor *exec, t_shell *shell);
int		execute_single_builtin(t_cmd *cmd, t_shell *shell);
int		execute_pipeline(t_cmd *cmd, t_shell *shell);
int	create_heredoc_fd(const char *delimiter, int expand_content, t_shell *shell);
int	execute_command(t_cmd *cmd, t_shell *shell);

# endif
#endif