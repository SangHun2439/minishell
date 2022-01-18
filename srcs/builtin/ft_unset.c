/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:41:14 by jeson             #+#    #+#             */
/*   Updated: 2022/01/18 12:22:14 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_form_unset(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (!is_valid_str(str) || ft_strchr(str, '='))
	{
		ft_putstr_fd("unset: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	is_envs_unset(t_cmd *cmd, char *argv, int *idx)
{
	char	**myenv;
	int		i;
	char	*tmp;
	int		res;

	myenv = *cmd->env_ptr;
	res = 0;
	*idx = -1;
	i = -1;
	while (myenv[++i])
	{
		tmp = ft_strndup(myenv[i], length_to_equ(myenv[i]));
		if (!ft_strcmp(tmp, argv))
		{
			*idx = i;
			res = 1;
		}
		free(tmp);
	}
	return (res);
}

char	**unset_env(t_cmd *cmd, int *idx)
{
	int		env_cnt;
	int		i;
	char	**myenv;
	char	**env_cpy;

	env_cnt = 0;
	myenv = *cmd->env_ptr;
	while (myenv[env_cnt])
		env_cnt++;
	env_cpy = (char **)malloc(sizeof(char *) * env_cnt);
	if (!env_cpy)
		return (init_err());
	i = -1;
	while (myenv[++i])
	{
		if (i + 1 == env_cnt)
			break ;
		if (i < *idx)
			env_cpy[i] = ft_strdup(myenv[i]);
		else
			env_cpy[i] = ft_strdup(myenv[i + 1]);
	}
	env_cpy[env_cnt - 1] = 0;
	free_split(myenv);
	return (env_cpy);
}

int	ft_unset(t_cmd *cmd)
{
	int	i;
	int	res;
	int	flg_form;
	int	idx;

	i = 0;
	flg_form = 0;
	while (cmd->argv[++i])
	{
		flg_form = is_valid_form_unset(cmd->argv[i]);
		if (flg_form == 1)
		{
			res = is_envs_unset(cmd, cmd->argv[i], &idx);
			if (res == 1)
				*cmd->env_ptr = unset_env(cmd, &idx);
			else
				continue ;
		}
	}
	return (0);
}
