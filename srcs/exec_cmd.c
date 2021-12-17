/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:30:38 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/17 21:36:46 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, char **path)
{
	char	*builtin;
	int		builtin_return;

	builtin = cmd->argv[0];
	(void)path;
	builtin_return = 0;
	if (!ft_strncmp(builtin, "echo", 5))
		builtin_return = 0;
		// ft_echo();
	else if (!ft_strncmp(builtin, "cd", 3))
		builtin_return = 0;
		// ft_cd();
	else if (!ft_strncmp(builtin, "pwd", 4))
		builtin_return = 0;
		// ft_pwd();
	else if (!ft_strncmp(builtin, "export", 7))
		builtin_return = 0;
		// ft_export();
	else if (!ft_strncmp(builtin, "unset", 6))
		builtin_return = 0;
		// ft_unset();
	else if (!ft_strncmp(builtin, "env", 4))
		builtin_return = 0;
		// ft_env();
	else if (!ft_strncmp(builtin, "exit", 5))
		builtin_return = 0;
		// ft_exit();
	else
		return (NOT_EXIST);
	return (EXIST);
}

int	exec_util(t_cmd *cmd, char **path)
{
	char	*full_path;
	pid_t	pid;

	while (*path)
	{
		full_path = get_full_path(cmd->argv[0], *path);
		if (file_exist(full_path))
		{
			pid = fork();
			if (pid == 0)
			{
				if (execve(full_path, cmd->argv, *(cmd->env_ptr)) == -1)
					return (err_handle2());
			}
			if (pid > 0)
				return (get_child_return(pid, full_path));
		}
		free(full_path);
		path++;
	}
	return (NOT_EXIST);
}

int	exec_ft(t_cmd *cmd, char **path)
{
	if (exec_builtin(cmd, path) == EXIST)
		return (SUCCESS);
	else if (exec_util(cmd, path) == EXIST)
		return (SUCCESS);
	else
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		g_last_status = 127;
		return (FAIL);
	}
}

int	exec_multi_cmd(t_list *cmd_list, char **path)
{
	int		res;
	int		multi_status;
	t_cmd	*first_cmd;

	res = 0;
	first_cmd = cmd_list->content;
	while (cmd_list)
	{
		multi_status = ((t_cmd *)(cmd_list->content))->multi_status;
		if (multi_status == REDIRECT_APPEND)
			res = redirect_append(first_cmd, cmd_list, path);
		else if (multi_status == REDIRECT_HEREDOC)
			res = redirect_heredoc(first_cmd, cmd_list, path);
		else if (multi_status == REDIRECT_INPUT)
			res = redirect_input(first_cmd, cmd_list, path);
		else if (multi_status == REDIRECT_OUTPUT)
			res = redirect_output(first_cmd, cmd_list, path);
		else if (multi_status == PIPE)
			res = _pipe(cmd_list, path);
		cmd_list = cmd_list->next;
	}
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
		return (err_handle2());
	if (!cmd_list->next)
		res = exec_ft(cmd_list->content, path);
	else
		res = exec_multi_cmd(cmd_list, path);
	free_split(path);
	return (res);
}
