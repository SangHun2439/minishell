/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:00:20 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/05 11:07:36 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "read_cmd.h"
# include "libft.h"
# include "signal_handler.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef struct	s_cmd
{
	// int main(int argc, char **argv)에서 argv와 같다고보면됨
	// 명령어 라인을 ' '(공백)으로 split한 문자열배열
	char	**argv;
	// 리다이렉션이나 파이프 상태를 저장하는 변수 ex) >, >>, |, <, <<
	// 상태는 아래에 상수로 define해둠
	char	multi_status;
}	t_cmd;

# define REDIRECT_INPUT 1
# define REDIRECT_OUTPUT 2
# define REDIRECT_HEREDOC 3
# define REDIRECT_APPEND 4
# define PIPE 5

# define TRUE 1
# define FALSE 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

void	err_handle1(void);
void	parse_cmd(t_list **cmd_list_ptr, char *line);
void	print_cmd_info(void *content);
void	del_cmd(void *content);

#endif
