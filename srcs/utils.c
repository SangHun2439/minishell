/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:11:36 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/05 11:06:25 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_info(void *content)
{
	t_cmd	*cmd;
	char	*str;
	int		idx;

	cmd = content;
	str = "none";
	idx = 0;
	while (cmd->argv[idx])
		printf("%s\n", cmd->argv[idx++]);
	if (cmd->multi_status == REDIRECT_INPUT)
		str = "input";
	if (cmd->multi_status == REDIRECT_OUTPUT)
		str = "output";
	if (cmd->multi_status == REDIRECT_APPEND)
		str = "append";
	if (cmd->multi_status == REDIRECT_HEREDOC)
		str = "heredoc";
	if (cmd->multi_status == PIPE)
		str = "pipe";
	printf("%s\n", str);
}
