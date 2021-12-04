/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:00:20 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/05 02:44:25 by sangjeon         ###   ########.fr       */
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
	// 명령어를 저장하는 변수 ex) echo, pwd ...
	char	*cmd;
	// 리다이렉션이나 파이프 상태를 저장하는 변수 ex) >, >>, |, <, <<
	char	multi_cmd;
	// 명령어에 전달할 값을 저장하는 변수
	// 옵션값도 같이 전달됨
	// ex)echo -n abc 일때 "-n abc"가 저장됨
	char	*arg;
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

t_cmd	*err_handle1(void);
void	parse_cmd(t_list **cmd_list_ptr, char *line);
void	print_cmd_info(void *content);
void	del_cmd(void *content);

#endif
