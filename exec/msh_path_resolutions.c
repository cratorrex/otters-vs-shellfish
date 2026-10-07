#include "minishell.h"

char	*get_path_value(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (ft_strdup(env[i] + 5));
		i++;
	}
	return (NULL);
}

char	*join_path_command(char *directory, size_t dir_len, char *cmd0)
{
	char	*prefix;
	char	*full;

	if (dir_len == 0)
		prefix = ft_strdup(".");
	else
		prefix = ft_substr(directory, 0, dir_len);
	if (!prefix)
		return (NULL);
	full = ft_strjoin(prefix, "/");
	free(prefix);
	if (!full)
		return (NULL);
	prefix = ft_strjoin(full, cmd0);
	free(full);
	return (prefix);
}

char	*resolve_command_path(char *cmd0, char **env)
{
	char	*path;
	char	*candidate;
	size_t	start;
	size_t	end;

	if (!cmd0 || !cmd0[0])
		return (NULL);
	if (ft_strchr(cmd0, '/'))
		return (ft_strdup(cmd0));
	path = get_path_value(env);
	if (!path)
		return (NULL);
	start = 0;
	while (1)
	{
		end = start;
		while (path[end] && path[end] != ':')
			end++;
		candidate = join_path_command(path + start, end - start, cmd0);
		if (!candidate)
			return (free(path), NULL);
		if (access(candidate, F_OK) == 0)
			return (free(path), candidate);
		free(candidate);
		if (!path[end])
			break ;
		start = end + 1;
	}
	free(path);
	return (NULL);
}

void clean_up_invalid_command(t_executor *exec, t_cmd *cmd)
{
	clean_up_cmd(cmd);
	clean_up_shell(exec->shell);
	free(exec->pids);
}

void	execute_external_command(t_cmd *cmd, t_executor *exec)
{
	char	*path;
	int		status;

	path = resolve_command_path(cmd->av[0], exec->shell->env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->av[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		clean_up_invalid_command(exec, exec->shell->cmds);
		exit(127);
	}
	execve(path, cmd->av, exec->shell->env);
	perror(cmd->av[0]);
	status = 126;
	if (errno == ENOENT)
		status = 127;
	free(path);
	clean_up_invalid_command(exec, exec->shell->cmds);
	exit(status);
}