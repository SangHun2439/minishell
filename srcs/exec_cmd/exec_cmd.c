/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:30:38 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/14 18:51:59 by jeson            ###   ########.fr       */
/*   Updated: 2022/01/05 11:42:28 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	exec_builtin(t_cmd *cmd, char **path)
{
	char	*cmd_name;

	cmd_name = cmd->argv[0];
	(void)path;
	
	if (!ft_strcmp(cmd_name, "echo"))
	 	return (ft_echo(cmd));
	else if (!ft_strcmp(cmd_name, "cd"))
	 	return (ft_cd(cmd));
	else if (!ft_strcmp(cmd_name, "pwd"))
	 	return (ft_pwd());
	else if (!ft_strcmp(cmd_name, "export"))
	 	return (ft_export(cmd));
	else if (!ft_strcmp(cmd_name, "unset"))
	 	return (ft_unset(cmd));
	else if (!ft_strcmp(cmd_name, "env"))
	 	return (ft_env(cmd));
	else if (!ft_strcmp(cmd_name, "exit"))
	 	return (ft_exit(cmd));
	return (NOCMD);
}

int	exec_util(t_cmd *cmd, char **path)
{
	char	*full_path;
	pid_t	pid;

	while (*path)
	{
		full_path = get_full_path(cmd->argv[0], *path);
		if (!full_path)
			return (1);
		if (file_exist(full_path))
		{
			pid = fork();
			if (pid == -1)
				return (execve_err());
			if (pid == 0)
			{
				if (execve(full_path, cmd->argv, *(cmd->env_ptr)) == -1)
					return (execve_err());
			}
			if (pid > 0)
				return (parents_do(pid, full_path));
		}
		free(full_path);
		path++;
	}
	return (NOCMD);
}

int	exec_ft_with_redi(t_cmd *cmd, char **path, int num)
{
	int	res;
	int	fd_stdout;
	int	fd_stdin;

	save_fd_std(&fd_stdout, &fd_stdin);
	res = redirect(cmd->redi_list, num);
	if (res != 0)
		return (end_exec_ft(res, fd_stdout, fd_stdin));
	res = exec_builtin(cmd, path);
	if (res != NOCMD)
		return (end_exec_ft(res, fd_stdout, fd_stdin));
	res = exec_util(cmd, path);
	if (res != NOCMD)
		return (end_exec_ft(res, fd_stdout, fd_stdin));
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	return (end_exec_ft(res, fd_stdout, fd_stdin));
}

void	errno_print(int	error, char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(error), STDERR_FILENO);
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
	return (0);
}

int	exec_ft(t_cmd *cmd, char **path, int num)
{
	int	res;

	if (cmd->redi_list)
		return (exec_ft_with_redi(cmd, path, num));
	res = exec_builtin(cmd, path);
	if (res != NOCMD)
		return (res);
	if (ft_strchr(cmd->argv[0], '/') != NULL)
		return (is_path(cmd->argv[0], cmd->argv, *(cmd->env_ptr)));
	res = exec_util(cmd, path);
	if (res != NOCMD)
		return (res);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	return (res);
}

int	exec_cmd(t_list *cmd_list)
{
	int		res;
	char	**path;
	char	*path_str;

	if (!cmd_list)
		return (0);
	path_str = getenv("PATH");
	// if (!path_str)
	// 	return (exec_path_err())
	path = ft_split(getenv("PATH"), ':');
	if (!path)
		return (1);
	if (!cmd_list->next)
		res = exec_ft(cmd_list->content, path, 0);
	else
		// res = exec_pipe(cmd_list, path);
		res = 0;
	exec_free_split(path);
	return (res);
}
