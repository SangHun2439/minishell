/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:21:43 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/03 13:08:01 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_exec_ft(int res, int fd_stdout, int fd_stdin)
{
	getback_fd_std(fd_stdout, fd_stdin);
	return (res);
}

int	end_redirect_err(void)
{
	exec_perr_and_init();
	return (1);
}

int	execve_err(void)
{
	exec_perr_and_init();
	return (1);
}

int	end_heredoc_err(char *fname)
{
	free(fname);
	exec_perr_and_init();
	return (1);
}
