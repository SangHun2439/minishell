CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INC = -Iincludes -Ilibft -I/opt/homebrew/opt/readline/include
LIB_NAME = ft
LIB_DIR = ./libft
LIB = -Llibft -L/opt/homebrew/opt/readline/lib -lft -lreadline
NAME = minishell

SRC_DIR = ./srcs/
SRC_NAME = main read_cmd sig_handler init init_err \
			parse_cmd parse_cmd2 parse_cmd_utils parse_cmd_utils2 parse_cmd_perr parse_cmd_errhandle parse_cmd_errhandle2\
			utils err_handle end_handle
			# exec_cmd redirect_pipe
SRCS = $(addsuffix .c ,$(addprefix $(SRC_DIR), $(SRC_NAME)))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB_NAME)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC) $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIB_NAME):
	@$(MAKE) -C $(LIB_DIR) all

clean:
	$(RM) $(OBJS)
	@$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
