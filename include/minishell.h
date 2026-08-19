#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>

/* parser.c */
char *rl_gets(void);
void free_line_buffer(char **line_buffer);



#endif
