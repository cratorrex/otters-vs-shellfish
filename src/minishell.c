#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#define ECHO "echo"

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

static char *line_read = (char *)NULL;

char	*rl_gets()
{
	if (line_read)
    {
		free (line_read);
		line_read = (char *)NULL;
	}
	line_read = readline("minishell>");
	if (!line_read)
		exit(0);
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
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
	char *rl_line_buffer;

	rl_line_buffer = NULL;
	while (1)
	{
		if (rl_line_buffer)
			rl_line_buffer = NULL;
		rl_line_buffer = rl_gets();
		if (!isfound_space(rl_line_buffer))
		{
			// process the rl_line_buffer here
			printf("%s\n", rl_line_buffer);
			
		}
	}
	
	return (0);
}
