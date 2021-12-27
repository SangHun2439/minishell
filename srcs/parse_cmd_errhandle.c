/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_errhandle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:25:51 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/28 00:35:13 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

int	parse_err_mem(void)
{
	perr_and_init();
	return (EMEMLACK);
}

int	parse_err_cmd(char **cmd_arr, int res)
{
	_free_split(cmd_arr);
	return (res);
}

int	parse_err_mem2(char **cmd_arr, t_cmd *cmd)
{
	perr_and_init();
	_free_split(cmd_arr);
	_free_split(cmd->argv);
	ft_lstclear(&(cmd->redi_list), del_redi_one);
	return (EMEMLACK);
}

int	parse_unexpected_err(const char *one_cmd)
{
	char	*info;
	int		status;

	if (!*one_cmd)
		info = "\\n";
	else
	{
		status = is_multi_cmd(one_cmd);
		if (status == REDIRECT_APPEND)
			info = ">>";
		else if (status == REDIRECT_INPUT)
			info = "<";
		else if (status == REDIRECT_OUTPUT)
			info = ">";
		else if (status == REDIRECT_HEREDOC)
			info = "<<";
		else
			info = "unknown character";
	}
	ft_putstr_fd("parse error near ", STDERR_FILENO);
	ft_putstr_fd(info, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EPARSE);
}

int	parse_unexpected_err2(void)
{
	ft_putstr_fd("parse error near '|'\n", STDERR_FILENO);
	return (EPARSE);
}
