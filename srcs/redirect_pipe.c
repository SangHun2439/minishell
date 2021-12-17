/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:56:46 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/12 21:39:00 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_append(t_cmd *first_cmd, t_list *cmd_list, char **path)
{
	t_cmd	*second_cmd;
	int		fd_tmp;
	int		fd;

	second_cmd = cmd_list->next->content;
	fd_tmp = dup(STDOUT);
	fd = open(second_cmd->argv[0], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		return (err_handle2());
	dup2(fd, STDOUT);
	exec_ft(first_cmd, path);
	dup2(fd_tmp, STDOUT);
	close(fd);
	return (0);
}

int	redirect_heredoc(t_cmd *first_cmd, t_list *cmd_list, char **path)
{
	(void)cmd_list;
	(void)first_cmd;
	(void)path;
	return (0);
}

int	redirect_input(t_cmd *first_cmd, t_list *cmd_list, char **path)
{
	t_cmd	*second_cmd;
	int		fd_tmp;
	int		fd;

	second_cmd = cmd_list->next->content;
	fd_tmp = dup(STDIN);
	fd = open(second_cmd->argv[0], O_RDONLY);
	if (fd < 0)
		return (err_handle2());
	dup2(fd, STDIN);
	exec_ft(first_cmd, path);
	dup2(fd_tmp, STDIN);
	close(fd);
	return (0);
}

int	redirect_output(t_cmd *first_cmd, t_list *cmd_list, char **path)
{
	t_cmd	*second_cmd;
	int		fd_tmp;
	int		fd;

	second_cmd = cmd_list->next->content;
	fd_tmp = dup(STDOUT);
	fd = open(second_cmd->argv[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (err_handle2());
	dup2(fd, STDOUT);
	exec_ft(first_cmd, path);
	dup2(fd_tmp, STDOUT);
	close(fd);
	return (0);
}

int	_pipe(t_list *cmd_list, char **path)
{
	(void)cmd_list;
	(void)path;
	return (0);
}
