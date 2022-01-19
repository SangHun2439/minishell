/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:20:57 by jeson             #+#    #+#             */
/*   Updated: 2022/01/19 17:01:24 by jeson            ###   ########.fr       */
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

void	env_overriding(char *env_key)
{
	t_list	*env_list;
	t_env	*env;

	env_list = g_vars.env_list;
	while (env_list)
	{
		env = env_list->content;
		if (!ft_strcmp(env, env->key))
			env->val = env_key;
		env_list = env_list->next;
	}
}

void	export_no_parm(void)
{
	t_list	*env_list;
	t_env	*env;

	env_list = g_vars.env_list;
	while (env_list)
	{
		env = env_list->content;
		if (find_value(env->key))
			printf("declare -x %s=\"%s\"\n", env->key, env->val);
		else
			printf("declare -x %s\n", env->key);
		env_list = env_list->next;
	}
}
