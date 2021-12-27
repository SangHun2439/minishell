/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:30:38 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/28 00:53:10 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

int	exec_builtin(t_cmd *cmd, char **path)
{
	char	*cmd_name;

	cmd_name = cmd->argv[0];
	(void)path;
	// if (!ft_strncmp(cmd_name, "echo", 5))
	// 	return (ft_echo());
	// else if (!ft_strncmp(cmd_name, "cd", 3))
	// 	return (ft_cd());
	// else if (!ft_strncmp(cmd_name, "pwd", 4))
	// 	return (ft_pwd());
	// else if (!ft_strncmp(cmd_name, "export", 7))
	// 	return (ft_export());
	// else if (!ft_strncmp(cmd_name, "unset", 6))
	// 	return (ft_unset());
	// else if (!ft_strncmp(cmd_name, "env", 4))
	// 	return (ft_env());
	// else if (!ft_strncmp(cmd_name, "exit", 5))
	// 	return (ft_exit());
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
			if (pid == 0)
			{
				if (execve(full_path, cmd->argv, *(cmd->env_ptr)) == -1)
					return (execve_err());
			}
			if (pid > 0)
				return (get_child_return(pid, full_path));
		}
		free(full_path);
		path++;
	}
	return (NOCMD);
}

int	exec_ft_with_redi(t_cmd *cmd, char **path)
{
	int	res;
	int	fd_stdout;
	int	fd_stdin;

	save_fd_std(&fd_stdout, &fd_stdin);
	res = redirect(cmd->redi_list);
	if (res != 0)
		return (end_exec_ft(res, fd_stdout, fd_stdin));
	res = exec_builtin(cmd, path);
	if (res != NOCMD)
		return (end_exec_ft(res, fd_stdout, fd_stdin));
	res = exec_util(cmd, path);
	if (res != NOCMD)
		return (end_exec_ft(res, fd_stdout, fd_stdin));
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (end_exec_ft(res, fd_stdout, fd_stdin));
}

int	exec_ft(t_cmd *cmd, char **path)
{
	int	res;

	if (cmd->redi_list)
		return (exec_ft_with_redi(cmd, path));
	res = exec_builtin(cmd, path);
	if (res != NOCMD)
		return (res);
	res = exec_util(cmd, path);
	if (res != NOCMD)
		return (res);
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (res);
}

int	exec_cmd(t_list *cmd_list)
{
	int		res;
	char	**path;

	if (!cmd_list)
		return (0);
	path = ft_split(getenv("PATH"), ':');
	if (!path)
		return (1);
	if (!cmd_list->next)
		res = exec_ft(cmd_list->content, path);
	else
		// res = exec_pipe(cmd_list, path);
		res = 0;
	exec_free_split(path);
	return (res);
}
