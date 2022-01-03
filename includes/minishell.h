/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:36:00 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/03 15:44:00 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "read_cmd.h"
# include "libft.h"
# include "parse_cmd.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>

int	g_last_status;

# define TRUE 1
# define FALSE 0

# define SUCCESS 0
# define FAIL 1

# define EXIST 0
# define NOT_EXIST 1

# define PWD_BUF_SIZE 200

# define NOCMD 127
# define RPIPE 0
# define WPIPE 1

int		redirect(t_list *redi_list, int num);
int		redirect_append(char *arg);
int		redirect_heredoc(char *arg, int num);
int		redirect_input(char *arg);
int		redirect_output(char *arg);
int		_pipe(t_list *cmd_lisr, char **path);
int		exec_cmd(t_list *cmd_list);
int		exec_ft(t_cmd *cmd, char **path, int num);
char	*get_full_path(char *each_cmd, char *each_path);
int		get_child_return(pid_t pid);
int		parents_do(pid_t pid, char *full_path);
int		file_exist(char *path);
void	getback_fd_std(int fd_stdout, int fd_stdin);
void	save_fd_std(int *fd_stdout, int *fd_stdin);
int		end_exec_ft(int res, int fd_stdout, int fd_stdin);
void	exec_perr_and_init(void);
int		end_redirect_err(void);
int		execve_err(void);
void	exec_free_split(char **str_arr);
char	*get_tmpf_name(int num);
int		end_heredoc_err(char *fname);
void	rlw_tmpf(int fd, char *arg);

void	err_handle1(void);
int		err_handle2(void);
void	*init_err(void);
void	print_cmd_info(void *content);
void	del_cmd(void *content);
void	free_split(char **str_arr);
int		init(char **argv, t_list **cmd_list_ptr, \
char **environ, char ***my_environ);
void	sig_handler(int sig);
void	*err_handle3(void);

#endif
