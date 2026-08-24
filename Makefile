NAME := minishell

CC := cc
CC_FLAGS := -Wall -Wextra -Werror -Iinclude
LD_FLAGS := -lreadline -lhistory

HEADER := minishell.h

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = \
	src/symbol_matcher.c \
	src/node_utils.c 	\
	src/operator.c 		\
	src/parser.c		\
	src/tokenizer.c 	\
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