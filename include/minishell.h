#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>

typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_APPEND,
    TOKEN_HEREDOC
}   t_token_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
    struct s_token  *next;
}   t_token;

typedef struct s_cmd
{
    char **av;
    char *redirs;
    struct s_cmd *next;
}   t_cmd;

typedef enum e_builtin_cmd
{
    ECHO,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT
}   t_builtin_cmd;

/* parser.c */
char *rl_gets(void);
void free_line_buffer(char **line_buffer);

/* tokenizer.c */
t_token *token_new(char *value, t_token_type type);
void token_add_back(t_token **lst, t_token *new);
void token_clear(t_token **lst);

void process_raw_line(char *line_read);




#endif
