/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 11:02:12 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/18 00:48:46 by sangjeon         ###   ########.fr       */
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
