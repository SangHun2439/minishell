/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:20:57 by jeson             #+#    #+#             */
/*   Updated: 2022/01/20 15:58:12 by jeson            ###   ########.fr       */
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
	char	*str_key;

	if (*cnt == 0)
		return ;
	env_list = g_vars.env_list;
	str_key = ft_strndup(str, length_to_equ(str));
	while (env_list)
	{
		env = env_list->content;
		split = ft_split(str, '=');
		if (!split)
			init_err();
		if (!ft_strcmp(env->key, str_key))
		{
			free(env->val);
			env->val = split[1];
		}
		env->flag = 0;
		env_list = env_list->next;
	}
	free(str_key);
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
