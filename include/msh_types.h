/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thtay <thtay@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 16:37:51 by thtay             #+#    #+#             */
/*   Updated: 2026/10/12 21:56:13 by jatansil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef MINISHELL_H
# ifndef MSH_TYPES_H
#  define MSH_TYPES_H

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
	TOKEN_HEREDOC,
	TOKEN_HEREDOC_QUOTED
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**av;
	t_redir			*redirs;
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
	EXIT,
	UNKNOWN_CMD
}	t_builtin_cmd;

typedef enum e_error_code
{
	SYNTAX_ERR,
	CMD_NOT_FOUND_ERR,
	UNCLOSED_BRACKET_ERR,
	GENERIC_ERR
}	t_error_code;

typedef struct s_shell
{
	char			**env;
	int				exit_status;
	int				should_exit;
	struct s_cmd	*cmds;
}	t_shell;

extern volatile sig_atomic_t	g_signal_interrupt;

# endif
#endif
