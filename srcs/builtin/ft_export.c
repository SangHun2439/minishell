/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:47:02 by jeson             #+#    #+#             */
/*   Updated: 2022/01/03 16:25:11 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_no_argv(t_cmd *cmd)
{
	char **envs;
	char **split;
	char *key;
	char *value;

	envs = *(cmd->env_ptr);
	while (*envs)
	{
		split = ft_split(*envs++, '=');
		key = *split++;
		value = *split;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(value, 1);
		ft_putendl_fd("\"", 1);
	}
}

/*
void	export_override(t_cmd *cmd, char *argv_ptr)
{
	char **argv_split;
	char *key_tmp;

	argv_split = ft_split(argv_ptr, '=');
	key_tmp = *argv_split;
	getenv
}
*/

int	is_valid(char *str)
{
	int	i;
	int idx;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			cnt++;
			idx = i;
		}
		i++;
	}
	if (cnt == 1 && (idx != 0 && idx != (i - 1)))
		return (0);
	return (1);
}

int	is_envs(char *tmp_env)
{
	if (!getenv(tmp_env))
		return (1);
	return (0);
}

int	ft_export(t_cmd *cmd)
{
	int	i;
	int	res;

	i = 1;
	if (!cmd->argv[1])
	{
		print_export_no_argv(cmd);
		return (0);
	}
	while (cmd->argv[i])
	{
		if (!is_valid(cmd->argv[i]))
			res = is_envs(cmd->argv[i]);
	/*	if (res == 0)
			export_override(cmd, cmd->argv[i]);
	*/	i++;
	}
	return (0);
}
