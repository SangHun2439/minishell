/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 15:56:00 by jeson             #+#    #+#             */
/*   Updated: 2021/12/07 17:25:04 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * builtin 함수 리턴 int ? void ?
 */

/*
int	exec_builtin(t_cmd *cmd, char **line)
{
	char	*builtin;

	builtin = cmd->argv;
	if (!ft_strcmp(builtin, "echo"))
		ft_echo(builtin, envs);
	else if (!ft_strcmp(builtin, "cd"))
		ft_cd();
	else if (!ft_strcmp(builtin, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(builtin, "export"))
		ft_export();
	else if (!ft_strcmp(builtin, "unset"))
		ft_unset();
	else if (!ft_strcmp(builtin, "env"))
		ft_env();
	else if (!ft_strcmp(builtin, "exit"))
		ft_exit();
	else
		return (0);
	return (1);
}
*/


int	exec_builtin(t_cmd *cmd, char **line)
{
	char	*builtin;
	int		builtin_return;

	builtin = cmd->argv;
	builtin_return = 0;
	if (!ft_strcmp(builtin, "echo"))
		bulitin_return = ft_echo(builtin, envs);
	else if (!ft_strcmp(builtin, "cd"))
		bulitin_return = ft_cd();
	else if (!ft_strcmp(builtin, "pwd"))
		bulitin_return = ft_pwd();
	else if (!ft_strcmp(builtin, "export"))
		bulitin_return = ft_export();
	else if (!ft_strcmp(builtin, "unset"))
		builtin_return = ft_unset();
	else if (!ft_strcmp(builtin, "env"))
		builtin_return = ft_env();
	else if (!ft_strcmp(builtin, "exit"))
		builtin_return = ft_exit();
	return (builtin_return);
}
