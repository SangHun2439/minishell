/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 11:02:12 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/20 22:02:21 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = content;
	free_split(cmd->argv);
	ft_lstclear(&(cmd->redi_list), del_redi_one);
	free(cmd);
}

void	init_err(void)
{
	put_errmsg();
	exit(1);
}

void	del_env_one(void *content)
{
	t_env	*env;

	env = content;
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->val)
		free(env->val);
	free(env);
}
