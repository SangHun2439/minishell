/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:11:36 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/05 02:36:46 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*err_handle1(void)
{
	ft_putstr_fd(strerror(errno), STDERR);
	exit(1);
	return (0);
}

void	print_cmd_info(void *content)
{
	t_cmd	*cmd;
	char	*str;

	cmd = content;
	str = "none";
	printf("%s\n", cmd->cmd);
	printf("%s\n", cmd->arg);
	if (cmd->multi_cmd == REDIRECT_INPUT)
		str = "input";
	if (cmd->multi_cmd == REDIRECT_OUTPUT)
		str = "output";
	if (cmd->multi_cmd == REDIRECT_APPEND)
		str = "append";
	if (cmd->multi_cmd == REDIRECT_HEREDOC)
		str = "heredoc";
	if (cmd->multi_cmd == PIPE)
		str = "pipe";
	printf("%s\n", str);
}

void	del_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = content;
	free(cmd->cmd);
	free(cmd->arg);
}
