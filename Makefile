NAME := minishell

CC := cc
CC_FLAGS := -Wall -Wextra -Werror -Iinclude -g
LD_FLAGS := -lreadline -lhistory

HEADER := minishell.h

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = \
<<<<<<< HEAD
	builtins/msh_cd.c				\
	builtins/msh_pwd.c				\
	builtins/msh_echo.c				\
	builtins/msh_exit.c 			\
	signal/msh_signal.c 			\
	src/helper/ft_strcmp.c 			\
	src/helper/symbol_matcher.c 	\
	src/helper/prompt_validator.c	\
	src/lexer/token_node_utils.c 	\
	src/lexer/operator.c 			\
	src/lexer/readline.c			\
	src/lexer/tokenizer.c 			\
	src/parser/redir_node_utils.c	\
	src/parser/cmd_node_utils.c 	\
	src/parser/parser.c 			\
	src/parser/expand_word.c 		\
	src/parser/expand_variable.c 	\
	src/parser/expand_command.c 	\
	src/environment_variable.c \
	src/debug_functions.c		\
	src/cleaner.c				\
=======
	builtins/msh_cd.c		\
	builtins/msh_pwd.c		\
	builtins/msh_echo.c		\
	builtins/msh_exit.c 	\
	exec/msh_pipexec.c		\
	exec/msh_pxheredoc.c	\
	signal/msh_signal.c 	\
	src/ft_strcmp.c 		\
	src/symbol_matcher.c 	\
	src/token_node_utils.c 	\
	src/operator.c 			\
	src/readline.c			\
	src/tokenizer.c 		\
	src/redir_node_utils.c	\
	src/cmd_node_utils.c 	\
	src/parser.c 			\
	src/expand_word.c 		\
	src/expand_variable.c 	\
	src/expand_command.c 	\
>>>>>>> develop
	src/minishell.c 


OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CC_FLAGS) $(OBJS) $(LIBFT) $(LD_FLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o:%.c include/minishell.h
	$(CC) $(CC_FLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all