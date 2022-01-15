/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:47:02 by jeson             #+#    #+#             */
/*   Updated: 2022/01/15 12:09:11 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export_no_argv(t_cmd *cmd)
{
	char **envs;
	char **split;
	char *key;
	char *value;

	envs = *cmd->env_ptr;
	while (*envs)
	{
		split = ft_split(*envs++, '=');
		key = split[0];
		value = split[1];
		printf("declare -x %s=\"%s\"\n", key, value);
		free_split(split);
	}
}

int		length_to_equ(char *s1)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != '=')
		i++;
	return (i);
}

char	**export_override(t_cmd *cmd, char *argv)
{
	int		len;
	int		i;
	int		env_cnt;
	char	**myenv;
	char	**env_cpy;

	env_cnt = 0;
	myenv = *cmd->env_ptr;
	while (myenv[env_cnt])
		env_cnt++;
	env_cpy = (char **)malloc(sizeof(char *) * (env_cnt + 1));
	i = -1;
	while (myenv[++i])
	{
		len = length_to_equ(myenv[i]);
		if (!ft_strncmp(myenv[i], argv, len))
			env_cpy[i] = ft_strdup(argv);
		else
			env_cpy[i] = ft_strdup(myenv[i]);
	}
	env_cpy[i] = 0;
	free_split(myenv);
	return (env_cpy);
}

int	is_valid_str(char *str)
{
	int	i;
	int	len_to_equ;
	int	flg_valid_str;

	flg_valid_str = 0;
	len_to_equ = length_to_equ(str);
	if (ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (i < len_to_equ)
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			flg_valid_str = 1;
		else
		{
			flg_valid_str = 0;
			break ;
		}
		i++;
	}
	if (flg_valid_str == 1)
		return (1);
	return (0);
}

int	is_valid_form_export(char *str)
{
	int	i;
	int idx;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!is_valid_str(str))
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
		return (0);
	}
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
		return (1);
	return (0);
}

int	is_envs_export(t_cmd *cmd, char *argv)
{
	char	**myenv;
	int	i;
	int	argv_len;

	myenv = *cmd->env_ptr;
	i = -1;
	while (myenv[++i])
	{
		argv_len = length_to_equ(argv);
		if (!ft_strncmp(argv, myenv[i], argv_len + 1))
			return (1);
	}
	return (0);
}

char	**export_env(t_cmd *cmd, char *argv)
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
	env_cpy[i] = (char *)malloc(sizeof(char) * (ft_strlen(argv) + 1));
	env_cpy[i] = ft_memcpy(env_cpy[i], argv, ft_strlen(argv) + 1);
	env_cpy[env_cnt + 1] = 0;
	free_split(myenv);
	return (env_cpy);
}

int	ft_export(t_cmd *cmd)
{
	int	i;
	int	res;
	int	flg_form;

	i = 1;
	flg_form = 0;
	if (!cmd->argv[1])
	{
		print_export_no_argv(cmd);
		return (0);
	}
	while (cmd->argv[i])
	{
		flg_form = is_valid_form_export(cmd->argv[i]);
		if (flg_form == 1)
		{
			res = is_envs_export(cmd, cmd->argv[i]);
			if (res == 1)
				*cmd->env_ptr = export_override(cmd, cmd->argv[i]);
			else
				*cmd->env_ptr = export_env(cmd, cmd->argv[i]);
		}
		i++;
	}
	return (0);
}
