/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 09:45:48 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/03 08:47:26 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

int	exec_pipe(t_list *cmd_list, char **path)
{
	int	pipe_fd[2];

	while (cmd_list)
	{
		cmd_list = cmd_list->next;
	}
	if(pipe(pipe_fd) == -1)
		return (0);
}
