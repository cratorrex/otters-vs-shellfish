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

// char	*rl_gets(char *line_read)
// {
// 	if (line_read)
//     {
// 		free (line_read);
// 		line_read = (char *) NULL;
// 	}
// 	line_read = readline("urprompt>");
// 	if (!line_read)
// 		exit(0);
// 	if (line_read && *line_read)
// 		add_history(line_read);
// 	return (line_read);
// }

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

int main(void)
{
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
		display_tokens(tokens);
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

/* For testing only, clean up later */
/*
int main(void)
{
	t_token *node_1;
    t_token *node_2;
    t_token *node_3;
    t_token *node_4;

    node_1 = token_new("echo", TOKEN_WORD);
    node_2 = token_new("hello", TOKEN_WORD);
    node_3 = token_new("|", TOKEN_PIPE);
    node_4 = token_new("cat", TOKEN_WORD);
    
    printf("node_1->value = %s\n", node_1->value);
    printf("node_1->type = %u\n", node_1->type);
    printf("node_2->value = %s\n", node_2->value);
    printf("node_2->type = %u\n", node_2->type);
    printf("node_3->value = %s\n", node_3->value);
    printf("node_3->type = %u\n", node_3->type);
    printf("node_4->value = %s\n", node_4->value);
    printf("node_4->type = %u\n", node_4->type);


    token_add_back(&node_1, node_2);
    token_add_back(&node_1, node_3);
    token_add_back(&node_1, node_4);
    printf("node_1->value = %s | node_1->type = %u\n", node_1->value, node_1->type);
    printf("node_2->value = %s | node_2->type = %u\n", node_1->next->value, node_1->next->type);
    printf("node_3->value = %s | node_3->type = %u\n", node_1->next->next->value, node_1->next->next->type);
    printf("node_4->value = %s | node_4->type = %u\n", node_1->next->next->next->value, node_1->next->next->next->type);


    token_clear(&node_1);
	char *res = ft_substr("Jason Nicholas Tansil", 0, 10);
	printf("|%s|", res);
	free(res);

}
*/
