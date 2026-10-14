/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jatansil <jatansil@42mail.sutd.edu.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 16:09:09 by jatansil          #+#    #+#             */
/*   Updated: 2026/10/12 21:57:39 by jatansil         ###   ########.fr       */
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

volatile sig_atomic_t	g_signal_interrupt = 0;

static int	process_parsed_command(t_cmd *cmd, t_token *tokens,
		t_shell *shell)
{
	if (tokens)
		token_clear(&tokens);
	if (collect_command_heredocs(cmd, shell) == -1)
	{
		clean_up_cmd(cmd);
		token_clear(&tokens);
		if (shell->exit_status != 130)
			shell->exit_status = 1;
		return (1);
	}
	execute_command(cmd, shell);
	clean_up_cmd(cmd);
	token_clear(&tokens);
	return (1);
}

static int	handle_empty_tokens(t_shell *shell)
{
	if (shell->exit_status == 1)
		shell->exit_status = 0;
	else
		shell->exit_status = 2;
	return (1);
}

static int	process_line(t_shell *shell, char *line)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = tokenizer(line, shell);
	if (!tokens)
		return (handle_empty_tokens(shell));
	if (!validate_syntax(tokens))
	{
		printf("minishell: syntax error\n");
		shell->exit_status = 2;
		token_clear(&tokens);
		return (1);
	}
	cmd = parse_token(tokens);
	if (!cmd)
		return (token_clear(&tokens), 0);
	if (!expand_command(cmd, shell))
	{
		clean_up_cmd(cmd);
		return (token_clear(&tokens), 0);
	}
	return (process_parsed_command(cmd, tokens, shell));
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	while (!shell->should_exit)
	{
		line = rl_gets();
		if (g_signal_interrupt == SIGINT)
		{
			shell->exit_status = 130;
			g_signal_interrupt = 0;
		}
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
	setup_interactive_signals();
	set_shell_level(&shell, get_env_value("SHLVL", shell.env));
	shell_loop(&shell);
	rl_clear_history();
	clean_up_shell(&shell);
	return (shell.exit_status);
}
