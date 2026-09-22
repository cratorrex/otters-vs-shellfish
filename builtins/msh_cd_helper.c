#include "minishell.h"

int	cd_set_variable(t_shell *shell, char *key, char *value)
{
	char	*tmp;
	char	*entry;
	char	**new_env;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (1);
	entry = ft_strjoin(tmp, value);
	free(tmp);
	if (!entry)
		return (1);
	if (get_target_variable_index(shell->env, key) != -1)
		new_env = update_variable(shell->env, entry);
	else
		new_env = add_new_variable(shell->env, entry);
	free(entry);
	if (!new_env)
		return (1);
	shell->env = new_env;
	return (0);
}

int	cd_update_env(t_shell *shell, char *oldpwd, char *newpwd)
{
	if (oldpwd)
	{
		if (cd_set_variable(shell, "OLDPWD", oldpwd))
			return (1);
	}
	if (cd_set_variable(shell, "PWD", newpwd))
		return (1);
	return (0);
}

int	cd_change_dir(t_shell *shell, char *path, int print_path)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = get_env_value("PWD", shell->env);
	if (oldpwd)
	{
		oldpwd = ft_strdup(oldpwd);
		if (!oldpwd)
			return (1);
	}
	if (chdir(path) == -1)
	{
		free(oldpwd);
		perror("msh: cd");
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		free(oldpwd);
		perror("msh: cd: getcwd");
		return (1);
	}
	if (cd_update_env(shell, oldpwd, newpwd))
	{
		free(oldpwd);
		free(newpwd);
		return (1);
	}
	if (print_path)
		ft_putendl_fd(newpwd, 1);
	free(oldpwd);
	free(newpwd);
	return (0);
}



