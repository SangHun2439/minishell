/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 11:02:12 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/05 11:15:11 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_cmd(void *content)
{
	t_cmd	*cmd;
	int		idx;

	cmd = content;
	idx = 0;
	while(cmd->argv[idx])
	{
		free(cmd->argv[idx]);
		idx++;
	}
	free(cmd->argv);
	free(cmd);
}
