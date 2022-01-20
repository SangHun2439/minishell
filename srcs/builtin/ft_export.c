/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:47:02 by jeson             #+#    #+#             */
/*   Updated: 2022/01/20 21:36:05 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_valid_form_export(char *str, int	*cnt)
{
	int	i;
	int	idx;

	i = -1;
	*cnt = 0;
	if (!is_valid_str(str))
	{
		ft_putstr_fd("export: `", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
		return (0);
	}
	while (str[++i])
	{
		if (str[i] == '=')
		{
			*cnt = 1;
			idx = i;
		}
	}
	if (idx != 0)
		return (1);
	return (0);
}

void	export_env(char *argv, int *cnt)
{
	t_list	*env_list;
	t_env	*env;
	char	**envp;

	envp = ft_split(argv, '=');
	if (!envp)
		init_err();
	env = malloc(sizeof(t_env));
	if (!env)
		init_err();
	env->key = envp[0];
	if (envp[1])
		env->val = envp[1];
	else
		env->val = ft_strdup("");
	if (*cnt > 0)
		env->flag = 0;
	else
		env->flag = 1;
	env_list = ft_lstnew(env);
	if (!env_list)
		init_err();
	ft_lstadd_back(&g_vars.env_list, env_list);
	free(envp);
}

int	ft_export(t_cmd *cmd)
{
	int	i;
	int	res;
	int	flg_form;
	int	cnt;

	i = 0;
	flg_form = 0;
	if (!cmd->argv[1])
	{
		export_no_parm();
		return (0);
	}
	while (cmd->argv[++i])
	{
		flg_form = is_valid_form_export(cmd->argv[i], &cnt);
		if (flg_form == 1)
		{
			res = is_key(cmd->argv[i]);
			if (res == 1)
				env_overriding(cmd->argv[i], &cnt);
			else
				export_env(cmd->argv[i], &cnt);
		}
	}
	return (0);
}
