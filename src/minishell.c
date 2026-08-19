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



int isfound_space(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int main(void)
{
	static char *rl_line_buffer;

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
		printf("You entered: %s\n", rl_line_buffer);
		/* let say here is */
		process_raw_line(rl_line_buffer);

		/* Wrong, only clean when shell exited / env not configured */
		if (ft_strncmp(rl_line_buffer, "clear", ft_strlen(rl_line_buffer)) == 0)
			rl_clear_history();
		/* if no longer used, clean up line buffer */
		free_line_buffer(&rl_line_buffer);
	}

	rl_clear_history();
	
	exit(0);
}
