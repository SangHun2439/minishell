/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 00:00:43 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/27 21:53:05 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CMD_H
# define PARSE_CMD_H

# include "libft.h"
# include <errno.h>
# include <string.h>
# include <unistd.h>

typedef struct	s_cmd
{
	// int main(int argc, char **argv)에서 argv와 같다고보면됨
	// 명령어 라인을 ' '(공백)으로 split한 문자열배열
	char	**argv;
	t_list	*redi_list;
	/* export, env함수에서 환경변수를 변경하기위해
	env_ptr를 가지고가서 역참조를 통해 변경*/
	char	***env_ptr;
}	t_cmd;

typedef struct s_redi
{
	// 리다이렉션 상태를 저장하는 변수 ex) >, >>, <, <<
	// 상태는 아래에 상수로 define해둠
	char	redi_status;
	char	*arg;
}	t_redi;

# define REDIRECT_INPUT 1
# define REDIRECT_OUTPUT 2
# define REDIRECT_HEREDOC 3
# define REDIRECT_APPEND 4
# define PIPE 5

# define EPARSE 258
# define EMEMLACK 1

# define EMPTYLINE -1

int		_isspace(char chr);
int		is_multi_cmd(const char *str);
void	redi_move_ptr(char **line_ptr, int redi_status);
char	**list_to_arr(t_list *list);
int	list_clear(t_list **cmd_line_list_ptr, t_list **redi_list_ptr);
void	del_redi_one(void *content);
int		mem_err_redi(t_redi *redi);
int		mem_err_redi2(t_redi *redi);
void	_free_split(char **str_arr);
int		fill_cmd_redi_list(char **one_cmd_ptr, \
t_list **cmd_line_list_ptr, t_list **redi_list_ptr);
int		parse_init(char **line_ptr, char ***cmd_arr_ptr);
int		case_cmd(char **one_cmd_ptr, t_list **cmd_line_list_ptr);
int		case_redi(char **one_cmd_ptr, t_list **redi_list_ptr, int redi_status);
char	*get_word_move_addr(char **str_ptr);
void	perr_and_init(void);
int		parse_err_mem(void);
int	parse_err_cmd(char **cmd_arr, int res);
int		parse_err_mem2(char **cmd_arr, t_cmd *cmd);
int		parse_unexpected_err(const char *one_cmd);

#endif
