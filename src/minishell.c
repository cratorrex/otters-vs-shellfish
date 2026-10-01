/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <jatansil@42mail.sutd.edu.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:09:09 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/01 16:13:30 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
*/

void	handle_sigint(int sig)
{
	(void) sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	init_shell(t_shell *shell, char **envp)
{
	if (!shell || !envp)
		return (0);
	shell->env = init_env_variable(envp);
	if (!shell->env)
		return (0);
	shell->exit_status = 0;
	shell->should_exit = 0;
	return (1);
}

static int	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = tokenizer(line);
	if (!tokens)
	{
		shell->exit_status = 2;
		return (1);
	}
	if (!validate_syntax(tokens))
	{
		printf("minishell: syntax error\n");
		shell->exit_status = 2;
		token_clear(&tokens);
		return (1);
	}
	cmd = parse_token(tokens);
	if (!cmd)
	{
		token_clear(&tokens);
		return (0);
	}
	if (!expand_command(cmd, shell))
	{
		clean_up_cmd(cmd);
		token_clear(&tokens);
		return (0);
	}
	execute_command(cmd, shell);
	clean_up_cmd(cmd);
	token_clear(&tokens);
	return (1);
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	while (!shell->should_exit)
	{
		line = rl_gets();
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (is_empty_prompt(line) || is_only_space(line))
		{
			free_line_buffer(&line);
			continue ;
		}
		if (!process_line(shell, line))
		{
			free_line_buffer(&line);
			shell->exit_status = 1;
			break ;
		}
		free_line_buffer(&line);
	}
}

int	main(int argc, char **av, char **envp)
{
	t_shell	shell;

	(void) av;
	if (argc != 1)
	{
		printf("Usage: ./minishell\n");
		return (1);
	}
	if (!init_shell(&shell, envp))
	{
		printf("minishell: failed to initialize shell\n");
		return (1);
	}
	signal(SIGINT, handle_sigint);
	shell_loop(&shell);
	clear_history();
	clean_up_shell(&shell);
	return (shell.exit_status);
}
