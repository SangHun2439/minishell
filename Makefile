CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
RM = rm -f
INC = -Iincludes -Ilibft -I/opt/homebrew/opt/readline/include
LIB_NAME = ft
LIB_DIR = ./libft
LIB = -Llibft -L/opt/homebrew/opt/readline/lib -lft -lreadline
NAME = minishell

SRC_DIR = ./srcs/
SRC_NAME = main read_cmd sig_handler init init_err \
			utils err_handle end_handle \
			./parse_cmd/parse_cmd ./parse_cmd/parse_cmd2 ./parse_cmd/parse_cmd_utils \
			./parse_cmd/parse_cmd_utils2 ./parse_cmd/parse_cmd_errhandle ./parse_cmd/parse_cmd_errhandle2 \
			./exec_cmd/exec_cmd ./exec_cmd/exec_cmd2 ./exec_cmd/exec_cmd_utils \
			./exec_cmd/exec_cmd_utils2 ./exec_cmd/exec_cmd_redi ./exec_cmd/exec_cmd_end \
			./builtin/ft_echo ./builtin/ft_pwd ./builtin/ft_export \
			./builtin/ft_env ./builtin/ft_exit ./builtin/ft_unset

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
