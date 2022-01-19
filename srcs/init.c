/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:11:45 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/19 16:44:01 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_to_list(char **envp)
{
	char	**one_env_arr;
	t_env	*env;
	t_list	*env_list;

	while (*envp)
	{
		one_env_arr = ft_split(*envp, '=');
		if (!one_env_arr)
			init_err();
		env = malloc(sizeof(t_env *));
		if (!env)
			init_err();
		env->key = one_env_arr[0];
		env->val = one_env_arr[1];
		env->flag = 0;
		env_list = ft_lstnew(env);
		if (!env_list)
			init_err();
		ft_lstadd_back(&g_vars.env_list, env_list);
		free(one_env_arr);
		envp++;
	}
}

int	init(char **argv, t_list **cmd_list_ptr, char **envp)
{
	char	*homepath;

	(void)argv;
	envp_to_list(envp);
	*cmd_list_ptr = 0;
	homepath = find_value("HOME");
	if (!homepath)
		init_err();
	homepath = ft_strdup(homepath);
	if (!homepath)
		init_err();
	g_vars.homepath = homepath;
	g_vars.last_status = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	return (0);
}
