/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_pipe2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 19:42:44 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/18 20:07:19 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_pipe(int *rpipe, int *wpipe)
{
	if (rpipe)
	{
		dup2(rpipe[RPIPE], STDIN_FILENO);
		close(rpipe[RPIPE]);
		close(rpipe[WPIPE]);
	}
	if (wpipe)
	{
		dup2(wpipe[WPIPE], STDOUT_FILENO);
		close(wpipe[WPIPE]);
		close(wpipe[RPIPE]);
	}
}

void	child_do_pipe(t_cmd *cmd, char **path, int **pipe_arr, int num)
{
	int	res;

	connect_pipe(pipe_arr[num], pipe_arr[num + 1]);
	if (cmd->redi_list)
	{
		res = redirect(cmd->redi_list);
		if (res != 0)
			exit(res);
	}
	res = exec_builtin(cmd);
	if (res != NOCMD)
		exit(res);
	if (ft_strchr(cmd->argv[0], '/') != NULL)
		is_path_pipe(cmd->argv[0], cmd->argv, *(cmd->env_ptr));
	res = exec_util_pipe(cmd, path);
	if (res != NOCMD)
		exit(res);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(res);
}

int	parents_do_pipe(pid_t pid, int **pipe_arr)
{
	int	res;
	int	status;
	int	i;

	res = 0;
	status = 0;
	i = 1;
	while (pipe_arr[i])
	{
		close(pipe_arr[i][RPIPE]);
		close(pipe_arr[i][WPIPE]);
		free(pipe_arr[i]);
		i++;
	}
	free(pipe_arr);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		res = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		res = 128 + WTERMSIG(status);
	while (wait(0) > 0)
		;
	errno = 0;
	return (res);
}
