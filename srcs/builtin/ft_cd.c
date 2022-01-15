/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:47:41 by jeson             #+#    #+#             */
/*   Updated: 2022/01/15 12:14:49 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

/*
 * getcwd(buf, size) : buf = NULL 이면 현재 작업 디렉토리 경로 가져옴
 * getcwd, chdir : 실패 하면 상세 오류 내용이 errno에 저장됨
 */

void	ft_errno(int error, char *dir)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(dir, STDERR_FILENO);
	ft_putendl_fd(strerror(error), STDERR_FILENO);
}

int	cd_home(t_cmd *cmd)
{
	if (chdir(cmd->home) < 0)
	{
		ft_errno(errno, cmd->home);
		return (1);
	}
	return (0);
}

int	cd_home_env(t_cmd *cmd)
{
	char *env_home;

	env_home = getenv("HOME");
	if (!env_home)
	{
		ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
		return (1);
	}
	if (!ft_strcmp(env_home, cmd->home))
		return (cd_home(cmd));
	else
	{
		if (chdir(env_home) < 0)
		{
			ft_errno(errno, env_home);
			return (1);
		}
	}
	return (0);
}

void	change_pwd(t_cmd *cmd)
{
	char	*old;
	char	*new;

	if (!getenv("PWD"))
		return ;
	old = ft_strjoin("OLDPWD=", getenv("PWD"));
	new = getcwd(NULL, 0);
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
		ft_errno(errno, cmd->argv[1]);
		return (1);
	}
	return (0);
}

int	relative_path(t_cmd *cmd)
{
	int	res;
	char	*tmp;
	char	*path_str;

	res = 0;
	tmp = cmd->argv[1];
	if (tmp[0] == '~')
	{
		if (tmp[1] == '/')
			path_str = ft_strjoin(cmd->home, &tmp[1]);
		else
			path_str = ft_strdup(tmp);
		if (chdir(path_str) < 0)
		{
			ft_errno(errno, tmp);
			res = 1;
		}
		free(path_str);
	}
	else if (chdir(tmp) < 0)
	{
		ft_errno(errno, tmp);
		res = 1;
	}
	return (res);
}

int	ft_cd(t_cmd	*cmd)
{
	char *tmp;
	int	res;

	tmp = cmd->argv[1];
	if (!tmp || !ft_strcmp(tmp, ""))
		res = cd_home_env(cmd);
	else if (!ft_strcmp(tmp, "~"))
		res = cd_home(cmd);
	else if (tmp[0] == '/')
		res = absolute_path(cmd);
	else
		res = relative_path(cmd);
	if (res == 0)
		change_pwd(cmd);
	return (res);
}
