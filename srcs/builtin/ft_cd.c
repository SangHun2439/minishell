/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:47:41 by jeson             #+#    #+#             */
/*   Updated: 2022/01/16 22:43:00 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

/*
 * getcwd(buf, size) : buf = NULL 이면 현재 작업 디렉토리 경로 가져옴
 * getcwd, chdir : 실패 하면 상세 오류 내용이 errno에 저장됨
 */

void	ft_cd_err(int error, char *dir)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(dir, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(error), STDERR_FILENO);
}

int	cd_home(char *tmp)
{
	char	*env_home;

	env_home = getenv("HOME");
	if (!env_home)
	{
		if (tmp && tmp[0] == '~')
		{
			if (chdir(g_vars.homepath) < 0)
			{
				ft_cd_err(errno, g_vars.homepath);
				return (1);
			}
			return (0);
		}
		else
			ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (1);
	}
	else
	{
		if (chdir(env_home) < 0)
		{
			ft_cd_err(errno, env_home);
			return (1);
		}
	}
	return (0);
}

void	change_pwd(t_cmd *cmd)
{
	char	*old;
	char	*new;
	char	*pwd;

	if (!getenv("PWD"))
		return ;
	old = ft_strjoin("OLDPWD=", getenv("PWD"));
	pwd = getcwd(NULL, 0);
	new = ft_strjoin("PWD=", pwd);
	free(pwd);
	*cmd->env_ptr = export_override(cmd, new);
	free(new);
	if (getenv("OLDPWD"))
		*cmd->env_ptr = export_override(cmd, old);
	free(old);
}

int	absolute_path(t_cmd *cmd)
{
	if (chdir(cmd->argv[1]) < 0)
	{
		ft_cd_err(errno, cmd->argv[1]);
		return (1);
	}
	return (0);
}

int	relative_path(t_cmd *cmd)
{
	int		res;
	char	*tmp;
	char	*path_str;

	res = 0;
	tmp = cmd->argv[1];
	if (tmp[0] == '~')
	{
		if (tmp[1] == '/')
			path_str = ft_strjoin(g_vars.homepath, &tmp[1]);
		else
			path_str = ft_strdup(tmp);
		if (chdir(path_str) < 0)
		{
			ft_cd_err(errno, path_str);
			res = 1;
		}
		free(path_str);
	}
	else if (chdir(tmp) < 0)
	{
		ft_cd_err(errno, tmp);
		res = 1;
	}
	return (res);
}

int	ft_cd(t_cmd	*cmd)
{
	int	res;

	if (!cmd->argv[1] || !ft_strcmp(cmd->argv[1], "") \
		|| !ft_strcmp(cmd->argv[1], "~"))
		res = cd_home(cmd->argv[1]);
	else if (*(cmd->argv[1]) == '/')
		res = absolute_path(cmd);
	else
		res = relative_path(cmd);
	if (res == 0)
		change_pwd(cmd);
	return (res);
}
