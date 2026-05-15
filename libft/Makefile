CC := cc
CC_FLAGS := -Wall -Wextra -Werror

HEADER := libft.h

AR := ar
AR_FLAGS := rcs
# > ar rcs Replace, Don't Warn, Create Archive 

SRC := ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c \
ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c \
ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
\
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
ft_lstiter.c ft_lstmap.c \
\
ft_printf/ft_printf.c ft_printf/ft_printf_handler.c \
ft_printf/ft_handle_char.c ft_printf/ft_handle_str.c \
ft_printf/ft_handle_int_dec.c ft_printf/ft_handle_uint.c \
ft_printf/ft_handle_hex.c ft_printf/ft_handle_point.c \
ft_printf/ft_handle_float.c \
\
get_next_line_bonus.c get_next_line_utils_bonus.c
# BONUS := 

OBJ := $(SRC:.c=.o)
# BONUS_OBJ := $(BONUS:.c=.o)

NAME := libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(AR_FLAGS) $(NAME) $(OBJ)
# $(NAME) $(OBJ) == $@ $^
# '$' is the control symbol
# '^' refers to all requirements
# '<' refers to first requirement (in this case $(OBJ))
# '@' output into NAME via $(NAME)

# bonus: $@ $(BONUS_OBJ)
#	$(AR) $(AR_FLAGS) $(NAME) $(BONUS_OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

# > make fclean 
# |> internally calls the commands in order 'clean >> fclean'

.PHONY: all clean fclean re
# bonus
