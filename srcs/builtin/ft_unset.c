/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:41:14 by jeson             #+#    #+#             */
/*   Updated: 2022/01/14 19:29:14 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length_to_equ_unset(const char *s1)
{
	size_t	len;

	len = 0;
	while (s1[len] != '=')
		len++;
	return (len);
}

int	is_valid_form_unset(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!is_valid_str(str) || ft_strchr(str, '='))
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd(": not a valid identifier", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	is_envs_unset(t_cmd *cmd, char *argv)
{
	char **myenv;
	int	i;
	int	len;

	myenv = *cmd->env_ptr;
	i = -1;
	while (myenv[++i])
	{
		len = length_to_equ_unset(myenv[i]);
		if (!ft_strncmp(argv, myenv[i], len))
			return (1);
	}
	return (0);
}

char	**unset_env(t_cmd *cmd, char *argv)
{
	int	len;
	int	env_cnt;
	int	i;
	int	j;
	char **myenv;
	char **env_cpy;

	env_cnt = 0;
	myenv = *cmd->env_ptr;
	while (myenv[env_cnt])
		env_cnt++;
	env_cpy = (char **)malloc(sizeof(char *) * env_cnt);
	if (!env_cpy)
		return (init_err());
	i = -1;
	j = -1;
	while (myenv[++i])
	{
		len = ft_strlen(argv);
		if (!ft_strncmp(myenv[i], argv, len))
			i++;
		j++;
		if (i == env_cnt)
			break ;
		len = ft_strlen(myenv[i]);
		env_cpy[j] = (char *)malloc(sizeof(char) * (len + 1));
		if (!env_cpy[j])
			return (init_err());
		ft_memcpy(env_cpy[j], myenv[i], (len + 1));
	}
	env_cpy[env_cnt - 1] = 0;
	return (env_cpy);
}

int	ft_unset(t_cmd * cmd)
{
	int	i;
	int	res;
	int	flg_form;

	i = 0;
	flg_form = 0;
	while (cmd->argv[++i])
	{
		flg_form = is_valid_form_unset(cmd->argv[i]);
		if (flg_form == 1)
		{
			res = is_envs_unset(cmd, cmd->argv[i]);
			if (res == 1)
				*cmd->env_ptr = unset_env(cmd, cmd->argv[i]);
			else
				break ;
		}
	}
	return (0);
}
