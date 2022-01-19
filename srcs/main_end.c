/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 11:02:12 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/19 16:41:10 by sangjeon         ###   ########.fr       */
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
