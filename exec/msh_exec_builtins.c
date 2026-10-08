#include "minishell.h"

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->av || !cmd->av[0])
		return (0);
	return (mexec_isbuiltin(cmd, shell));
}

int	execute_single_builtin(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		perror("minishell: dup");
		if (saved_stdin >= 0)
			close(saved_stdin);
		if (saved_stdout >= 0)
			close(saved_stdout);
		return (1);
	}
	status = 0;
	if (setup_redirections(cmd->redirs, shell) == -1)
		status = 1;
	else
		status = execute_builtin(cmd, shell);
	if (restore_standard_fds(saved_stdin, saved_stdout) == -1)
		status = 1;
	shell->exit_status = status;
	return (status);
}
