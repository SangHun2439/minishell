/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 14:39:58 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/17 21:19:37 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errno_print(int	error, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(error), STDERR_FILENO);
	errno = 0;
}

int	is_path(char *str, char **argv, char **env)
{
	pid_t	pid;

	if (is_direc(str))
	{
		errno_print(EISDIR, str);
		return (126);
	}
	pid = fork();
	if (pid == -1)
		return (execve_err());
	if (pid == 0)
	{
		execve(str, argv, env);
		errno_print(errno, str);
		if (errno == ENOENT)
			exit (127);
		if (errno == EACCES)
			exit (126);
		exit (126);
	}
	if (pid > 0)
		return (parents_do(pid, NULL));
	return (NODO);
}

int	parents_do(pid_t pid, char *full_path)
{
	int		status;
	int		res;

	if (full_path)
		free(full_path);
	res = 0;
	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		res = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		res = 128 + WTERMSIG(status);
	return (res);
}

int	child_do(char *full_path, char **argv, char **envp)
{
	if (execve(full_path, argv, envp) == -1)
	{
		exec_perr_and_init();
		exit (FAIL);
	}
	return (0);
}
