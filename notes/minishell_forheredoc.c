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

/* 
readline -> reading a prompt from a prompt, return the read line buff minus the newline and the prompt name
add_history -> adding every prompt to the history list, it will be stored every time we navigate thru arrow up
rl_on_new_line ->
rl_clear_history ->
rl_replace_line ->
rl_redisplay -> 

access ->
wait ->
waitpid ->
wait3 ->
wait4 ->

signal ->
sigaction ->
sigemptyset ->
sigaddset ->

kill ->
exit ->
getcwd ->
chdir ->

stat ->
lstat ->
fstat ->
unlink ->
execve ->
*/

void handle_sigint(int sig)
{
    (void)sig;

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
	t_cmd		*cmd;

	tokens = tokenizer(line);
	if (!tokens)
	{
		shell->exit_status = 2;
		return (1);
	}
	if (!validate_syntax(tokens))
	{
		printf("syntax error\n");
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
	print_cmd_list(cmd);
	msh_exec_one(cmd, shell);
	// execute_commands(cmd, shell);
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

	(void)av;
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

// int main(int argc, char **av, char **envp)
// {
// 	static char *rl_line_buffer;
// 	t_token *tokens;
// 	t_shell shell;
	
// 	tokens = NULL;
// 	rl_line_buffer = NULL;
// 	if (argc != 1 && !*av)
// 	{
// 		printf("Usage: ./minishell\n");
// 		return (1);
// 	}
// 	if (!envp)
// 	{
// 		printf("Error: default environement path does not exist\n");
// 		return (1);
// 	}
// 	signal(SIGINT, handle_sigint);
// 	while (1)
// 	{
// 		rl_line_buffer = rl_gets();

// 		//// Clean up later
// 		/* handle signal CTRL + D */
// 		if (!rl_line_buffer)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		/* handle empty prompt & prompt that contains only spaces */
// 		if (is_empty_prompt(rl_line_buffer) || is_only_space(rl_line_buffer))
// 		{
// 			free_line_buffer(&rl_line_buffer);
// 			continue ;
// 		}
// 		////
	
// 		//// TOKENIZER
// 		/* tokenize word from rl_line_buffer based on token type */
// 		tokens = tokenizer(rl_line_buffer);
// 		if (!tokens)
// 		{
// 			free_line_buffer(&rl_line_buffer);
// 			exit(1);
// 		}
// 		if (!validate_syntax(tokens))
// 		{
// 			printf("syntax error\n");
// 			free_line_buffer(&rl_line_buffer);
// 			token_clear(&tokens);
// 			/* return back exit code */
// 			continue ;
// 		}
// 		////


// 		//// PARSER
// 		/* parsing token into command structure */
// 		shell.commands = parse_token(tokens);
// 		if (!shell.commands)
// 		{
// 			printf("commands is NULL\n");
// 			exit(1);
// 		}
	
// 		printf("Before expansion\n");
// 		print_cmd_list(shell.commands);
// 		/* preparing the command for expansion of variable and quote removal */

// 		shell.envp = init_env_variable(envp);
// 		shell.exit_status = 0;
		
// 		if (!expand_command(shell.commands, &shell))
// 		{
// 			free_line_buffer(&rl_line_buffer);
// 			token_clear(&tokens);
// 			clean_up_cmd(shell.commands);
// 			clean_up_arr_str(shell.envp);
// 			exit(1);
// 		}
// 		printf("\n\nAfter expansion\n");
// 		print_cmd_list(shell.commands);

// 		// printf("Calling msh_exec()\n");
// 		int pwd_status = msh_pwd(2, shell.envp);
// 		printf("pwd_status = %d\n", pwd_status);


// 		int cd_status = msh_cd(2, shell.commands->av);
// 		printf("cd_status = %d\n", cd_status);
// 		printf("\n\n\n\n\n");

// 		int env_status = msh_env(&shell);
// 		printf("env_status = %d\n", env_status);
// 		printf("\n\n\n\n\n");

// 		int export_status = msh_export(&shell, "TEST1=hello");
// 		printf("export_status = %d\n", export_status);

// 		int unset_status = msh_unset(&shell, "TEST");
// 		print_env(shell.envp);
// 		printf("unset_status = %d\n", unset_status);
		
// 		printf("\n\n\n\n\n");



// 		////

// 		// Execution part
// 		// process_shell(&shell);


// 		/* Wrong, only clean when shell exited / env not configured */
// 		if (ft_strncmp(rl_line_buffer, "clear", ft_strlen(rl_line_buffer)) == 0)
// 			rl_clear_history();
		
// 		/* Clean up everything */
// 		clean_up_arr_str(shell.envp);
// 		clean_up_cmd(shell.commands);
// 		token_clear(&tokens);
// 		free_line_buffer(&rl_line_buffer);
// 	}

// 	rl_clear_history();
	
// 	exit(0);
// }