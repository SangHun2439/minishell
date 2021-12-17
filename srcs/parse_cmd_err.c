/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 16:25:51 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/18 00:48:12 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

int	parse_unexpected_err(void)
{
	errno = EPARSE;
	return (0);
}

int	mem_err_redi(t_redi *redi)
{
	free(redi);
	return (0);
}

int	mem_err_redi2(t_redi *redi)
{
	free(redi->arg);
	free(redi);
	return (0);
}

int	err_parse_cmd(char **cmd_arr)
{
	_free_split(cmd_arr);
	return (0);
}

int	mem_err_parse_cmd(char **cmd_arr, t_cmd *cmd)
{
	_free_split(cmd_arr);
	_free_split(cmd->argv);
	ft_lstclear(&(cmd->redi_list), del_redi_one);
	return (0);
}
