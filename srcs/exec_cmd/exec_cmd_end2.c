/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_end2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 19:27:59 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/17 21:52:11 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fork_err(char *full_path)
{
	free(full_path);
	exec_perr_and_init();
	return (1);
}

int	execve_err_pipe(void)
{
	exec_perr_and_init();
	while (wait(0) > 0)
		;
	errno = 0;
	return (1);
}

int	**pipe_init_err(int **pipe_arr, int end)
{
	int	i;

	put_errmsg();
	i = 0;
	while (i < end)
	{
		close(pipe_arr[i][RPIPE]);
		close(pipe_arr[i][WPIPE]);
		free(pipe_arr[i]);
		i++;
	}
	free(pipe_arr[end]);
	free(pipe_arr);
	return (0);
}

int	**pipe_init_alloc_err(int **pipe_arr, int end)
{
	int i;

	put_errmsg();
	i = 0;
	while (i < end)
	{
		close(pipe_arr[i][RPIPE]);
		close(pipe_arr[i][WPIPE]);
		free(pipe_arr[i]);
		i++;
	}
	free(pipe_arr);
	return (0);
}
