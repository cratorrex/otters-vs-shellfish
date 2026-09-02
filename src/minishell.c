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
		if (!rl_line_buffer)
		{
			printf("exit\n");
			break ;
		}
		
		/* process line buffer here */
		tokens = tokenizer(rl_line_buffer);
		if (!validate_syntax(tokens))
		{
			printf("syntax error\n");
			token_clear(&tokens);
			exit(1);
		}
		if (!envp)
			return (1);
		t_cmd *commands = parse_token(tokens);
		if (!commands)
			printf("commands is NULL\n");
		else
			print_cmd_list(commands);
		/* preparing the command for expansion of variable and quote removal */
		t_shell *shell;

		shell = NULL;
		if (!envp)
			shell->envp = envp;
		
		token_clear(&tokens);
		/* Wrong, only clean when shell exited / env not configured */
		if (ft_strncmp(rl_line_buffer, "clear", ft_strlen(rl_line_buffer)) == 0)
			rl_clear_history();
		/* if no longer used, clean up line buffer */
		free_line_buffer(&rl_line_buffer);
	}

	rl_clear_history();
	
	exit(0);
}