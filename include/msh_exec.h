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


typedef int	t_mpx_fd[2];
t_mpx_fd	*msh_pipexec(t_cmd *cmd);
int	msh_exec_one(t_cmd *cmd, t_shell *shell);
int	mexec_find_path(char **found, char *path, char *cmd0);
int	mexec_isbuiltin(t_cmd *cmd, t_shell *shell);

t_builtin_cmd is_builtin_cmd(char *cmd);

//if delim has quotes there should be a notice of it.
//mode1 means we expand environment
//mode0 means the delim was quoted 
// int	msh_pxheredoc(char *delimiter, int mode);
t_mpx_fd	*mpx_traverse_pipe(t_cmd *cmd);
// int	mpx_traverse_left(t_cmd *pass, t_mpx_fd **store);
// int mpx_traverse_right(t_cmd *pass, t_mpx_fd **store);

//int	msh_exec(t_cmd *cmd, t_env *sumshi);


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
void		execute_external_command(t_cmd *cmd, t_executor *exec);
int		wait_for_children(t_executor *exec, t_shell *shell);
int		execute_single_builtin(t_cmd *cmd, t_shell *shell);
int		execute_pipeline(t_cmd *cmd, t_shell *shell);
int	create_heredoc_fd(const char *delimiter, int expand_content, t_shell *shell);
int	execute_command(t_cmd *cmd, t_shell *shell);

# endif
#endif