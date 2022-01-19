/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:20:57 by jeson             #+#    #+#             */
/*   Updated: 2022/01/19 16:41:27 by jeson            ###   ########.fr       */
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

void	env_overriding(char *argv)
{
	t_list	*env;
	char	*tmp;

	env = g_var.env_list;
	while (env)
	{
		if (!ft_strcmp(env, env->key))
			env->value = argv;
		env = env->next;
	}
}

void	export_no_parm(void)
{
	t_list	*env;

	env = g_var.env_list;
	while (env)
	{
		if (find_value(env->key))
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}
