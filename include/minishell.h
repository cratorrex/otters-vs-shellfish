#ifndef MINISHELL_H
# define MINISHELL_H
// # define _POSIX_C_SOURCE

# include "libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
//#  define __USE_POSIX	//this is for the squiggles. ONLY USE FOR TESTING
# include <signal.h>
# include <errno.h>

# include "msh_signal.h"
# include "msh_builtins.h"

typedef enum e_quote_state
{
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	QUOTE_NONE
}	t_quote_state;

typedef enum e_lex_status
{
	LEX_OK,
	LEX_MALLOC_ERROR,
	LEX_UNCLOSED_QUOTE
}	t_lex_status;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**av;
	char			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_builtin_cmd
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtin_cmd;

/* parser.c */
char			*rl_gets(void);
void			free_line_buffer(char **line_buffer);

/* symbol_matcher */
int				isfound_space(char *line);
int				is_delimiter(char c);
int				is_operator(char c);

/* node_utils.c */
t_token			*token_new(char *value, t_token_type type);
void			token_add_back(t_token **lst, t_token *new);
void			token_clear(t_token **lst);

/* operator.c */
t_token_type	classify_operator(char *line);

/* tokenizer.c */
t_token			*tokenizer(char *line_read);

//
//

#endif
