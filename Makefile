CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INC = -Iincludes
NAME = minishell

SRC_DIR = ./srcs/
SRC_NAME =
SRCS = $(addsuffix .c ,$(addprefix $(SRC_DIR), $(SRC_NAME)))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
