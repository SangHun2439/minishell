/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:20:57 by jeson             #+#    #+#             */
/*   Updated: 2022/01/20 22:28:12 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_err(int error, char *dir)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(dir, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(error), STDERR_FILENO);
}

int	length_to_equ(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	env_overriding(char *str, int *cnt)
{
	t_list	*env_list;
	t_env	*env;
	char	**split;

	if (*cnt == 0)
		return ;
	env_list = g_vars.env_list;
	split = ft_split(str, '=');
	if (!split)
		init_err();
	while (env_list)
	{
		env = env_list->content;
		if (!key_cmp(env->key, str))
		{
			free(env->val);
			if (!split[1])
				env->val = ft_strdup("");
			else
				env->val = ft_strdup(split[1]);
		}
		env->flag = 0;
		env_list = env_list->next;
	}
	free_split(split);
}

void	export_no_parm(void)
{
	t_list	*env_list;
	t_env	*env;

	env_list = g_vars.env_list;
	while (env_list)
	{
		env = env_list->content;
		if (env->flag == 0)
			printf("declare -x %s=\"%s\"\n", env->key, env->val);
		else if (env->flag == 1)
			printf("declare -x %s\n", env->key);
		env_list = env_list->next;
	}
}
