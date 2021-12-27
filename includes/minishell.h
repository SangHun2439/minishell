/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:36:00 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/27 22:39:42 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "read_cmd.h"
# include "libft.h"
# include "signal_handler.h"
# include "parse_cmd.h"
# include "exec_cmd.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

// 가장 최근 프로그램의 종료상태를 저장하기위한 변수
int	g_last_status;

# define TRUE 1
# define FALSE 0

# define SUCCESS 0
# define FAIL 1

# define EXIST 0
# define NOT_EXIST 1

# define PWD_BUF_SIZE 200

void	err_handle1(void);
int		err_handle2(void);
void	*init_err(void);
void	print_cmd_info(void *content);
void	del_cmd(void *content);
void	free_split(char **str_arr);
int		init(char **argv, t_list **cmd_list_ptr, char **environ, char ***my_environ);
void	*err_handle3(void);

#endif
