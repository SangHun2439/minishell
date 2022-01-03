/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:56:00 by jeson             #+#    #+#             */
/*   Updated: 2022/01/03 10:33:49 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_cmd *cmd, char **line)
{
	char	*builtin;
	int		builtin_return;

	builtin = cmd->argv;
	builtin_return = 0;
	if (!ft_strcmp(builtin, "echo"))
		builtin_return = ft_echo(builtin, envs);
	else if (!ft_strcmp(builtin, "cd"))
		builtin_return = ft_cd();
	else if (!ft_strcmp(builtin, "pwd"))
		builtin_return = ft_pwd();
	else if (!ft_strcmp(builtin, "export"))
		builtin_return = ft_export();
	else if (!ft_strcmp(builtin, "unset"))
		builtin_return = ft_unset();
	else if (!ft_strcmp(builtin, "env"))
		builtin_return = ft_env();
	else if (!ft_strcmp(builtin, "exit"))
		builtin_return = ft_exit();
	return (builtin_return);
}
