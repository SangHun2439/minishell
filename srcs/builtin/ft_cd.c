/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:47:41 by jeson             #+#    #+#             */
/*   Updated: 2022/01/18 12:24:16 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_home(char *tmp)
{
	if (!getenv("HOME"))
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
		if (chdir(getenv("HOME")) < 0)
		{
			ft_cd_err(errno, getenv("HOME"));
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
	*cmd->env_ptr = env_overriding(cmd, new);
	free(new);
	if (getenv("OLDPWD"))
		*cmd->env_ptr = env_overriding(cmd, old);
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
