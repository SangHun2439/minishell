/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:47:02 by jeson             #+#    #+#             */
/*   Updated: 2022/01/05 15:03:20 by jeson            ###   ########.fr       */
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

int		length_to_equ(char *s1)
{
	int	i;

	i = 0;
	while (s1[i] != '=')
		i++;
	return (i);
}

void	export_override(t_cmd *cmd, char *argv_ptr)
{
	char	*export_key;
	int		len;
	int		i;
	char	**myenv;

	i = 0;
	len = 0;
	myenv = *cmd->env_ptr;
	export_key = (char *)malloc(sizeof(char) * (length_to_equ(argv_ptr) + 1));
	ft_memcpy(export_key, argv_ptr, length_to_equ(argv_ptr) + 1);
	while (myenv[i])
	{
		len = length_to_equ(myenv[i]);
		if (!ft_strncmp(myenv[i], export_key, len))
		{
			free(myenv[i]);
			myenv[i] = (char *)malloc(sizeof(char) * (ft_strlen(argv_ptr) + 1));
			ft_memcpy(myenv[i], argv_ptr, ft_strlen(argv_ptr) + 1);
		}
		i++;;
	}
}

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
	if (cnt == 1 && idx != 0)
		return (0);
	return (1);
}

int	is_envs(char *tmp_env)
{
	char **env_split;

	env_split = ft_split(tmp_env, '=');
	if (!getenv(*env_split))
		return (1);
	return (0);
}

char	**export_env(t_cmd *cmd, char *argv_ptr)
{
	int		len;
	int		env_cnt;
	int		i;
	char	**myenv;
	char	**env_cpy;

	env_cnt = 0;
	myenv = *cmd->env_ptr;
	while (myenv[env_cnt])
		env_cnt++;
	env_cpy = (char **)malloc(sizeof(char *) * (env_cnt + 2));
	if (!env_cpy)
		return (init_err());
	i = 0;
	while (i < env_cnt)
	{
		len = ft_strlen(myenv[i]);
		env_cpy[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!env_cpy[i])
			return (init_err());
		env_cpy[i] = ft_memcpy(env_cpy[i], myenv[i], (len + 1));
		i++;
	}
	env_cpy[i] = (char *)malloc(sizeof(char) * (ft_strlen(argv_ptr) + 1));
	env_cpy[i] = ft_memcpy(env_cpy[i], argv_ptr, ft_strlen(argv_ptr) + 1);
	env_cpy[env_cnt + 1] = 0;
	return (env_cpy);
}

int	ft_export(t_cmd *cmd)
{
	int	i;
	int	res;
	int	flg_form;
	char	**myenviron;

	i = 1;
	flg_form = 0;
	myenviron = *cmd->env_ptr;
	if (!cmd->argv[1])
	{
		print_export_no_argv(cmd);
		return (0);
	}
	while (cmd->argv[i])
	{
		if (!is_valid(cmd->argv[i]))
			res = is_envs(cmd->argv[i]);
		if (res == 0)
			export_override(cmd, cmd->argv[i]);
		else
			*cmd->env_ptr = export_env(cmd, cmd->argv[i]);
		i++;
	}
	return (0);
}
