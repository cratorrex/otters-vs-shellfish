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

/*display token for debugging, clean up later*/
void display_tokens(t_token *tokens)
{
	int index = 0;
	while (tokens)
	{
		index++;
		printf("token %d value = %s | type = %d\n", index, tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

void	print_cmd_list(t_cmd *cmd)
{
	int		i;
	int		cmd_index;
	t_redir	*redir;

	cmd_index = 0;
	while (cmd)
	{
		printf("\n========== CMD %d ==========\n", cmd_index);

		printf("Arguments:\n");
		if (!cmd->av)
			printf("  (none)\n");
		else
		{
			i = 0;
			while (cmd->av[i])
			{
				printf("  av[%d] = \"%s\"\n", i, cmd->av[i]);
				i++;
			}
		}

		printf("Redirections:\n");
		if (!cmd->redirs)
			printf("  (none)\n");
		else
		{
			redir = cmd->redirs;
			while (redir)
			{
				printf("  type = %d, target = \"%s\"\n",
					redir->type, redir->target);
				redir = redir->next;
			}
		}

		printf("============================\n");

		cmd = cmd->next;
		cmd_index++;
	}
}

// void executor_dummy(t_cmd *commands, t_shell *shell)
// {
	
// }

int is_empty_prompt(const char *line_read)
{
	return (ft_strlen(line_read) == 0);
}

int is_only_space(const char *line_read)
{
	int i;
	int len;

	i = 0;
	while (line_read[i] && line_read[i] == ' ')
		i++;
	len = ft_strlen(line_read);
	if (len == i)
		return (1);
	return (0);
}

int main(int argc, char **av, char **envp)
{
	if (argc != 1 && !*av)
	{
		printf("Usage: ./minishell\n");
		return (1);
	}
	static char *rl_line_buffer;
	t_token *tokens;

	tokens = NULL;
	signal(SIGINT, handle_sigint);
	rl_line_buffer = NULL;
	while (1)
	{
		rl_line_buffer = rl_gets();

		//// Clean up later
		/* handle signal CTRL + D */
		if (!rl_line_buffer)
		{
			printf("exit\n");
			break ;
		}
		/* handle empty prompt & prompt that contains only spaces */
		if (is_empty_prompt(rl_line_buffer) || is_only_space(rl_line_buffer))
		{
			free_line_buffer(&rl_line_buffer);
			continue ;
		}
		////


		
		//// TOKENIZER
		/* tokenize word from rl_line_buffer based on token type */
		tokens = tokenizer(rl_line_buffer);
		if (!validate_syntax(tokens))
		{
			printf("syntax error\n");
			free_line_buffer(&rl_line_buffer);
			token_clear(&tokens);
			/* return back exit code */
			continue ;
		}
		if (!envp)
		{
			printf("environment path not found\n");
			free_line_buffer(&rl_line_buffer);
			token_clear(&tokens);
			exit(1);
		}
		////


		//// PARSER
		/* parsing token into command structure */
		t_cmd *commands = parse_token(tokens);
		if (!commands)
			printf("commands is NULL\n");
		else
		{
			printf("Before expansion\n");
			print_cmd_list(commands);
		}
		/* preparing the command for expansion of variable and quote removal */
		t_shell shell;

		shell.envp = envp;
		shell.exit_status = 0;
		
		if (!expand_command(commands, &shell))
		{
			free_line_buffer(&rl_line_buffer);
			token_clear(&tokens);
			/* clean up command structure */
			exit(1);
		}
		printf("\n\nAfter expansion\n");
		print_cmd_list(commands);
		token_clear(&tokens);
		////

		/* Wrong, only clean when shell exited / env not configured */
		if (ft_strncmp(rl_line_buffer, "clear", ft_strlen(rl_line_buffer)) == 0)
			rl_clear_history();
		/* if no longer used, clean up line buffer */
		free_line_buffer(&rl_line_buffer);
	}

	rl_clear_history();
	
	exit(0);
}