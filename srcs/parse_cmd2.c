/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:04:30 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/24 09:46:35 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

int	parse_init(char **line_ptr, char ***cmd_arr_ptr)
{
	while (**line_ptr && _isspace(**line_ptr))
		(*line_ptr)++;
	if (!(**line_ptr))
		return (0);
	*cmd_arr_ptr = ft_split(*line_ptr, '|');
	if (!*cmd_arr_ptr)
		return (parse_err_mem());
	return (1);
}

int	fill_cmd_redi_list(char **one_cmd_ptr, \
t_list **cmd_line_list_ptr, t_list **redi_list_ptr)
{
	int		redi_status;

	redi_status = is_multi_cmd(*one_cmd_ptr);
	if (!redi_status)
	{
		if (!case_cmd(one_cmd_ptr, cmd_line_list_ptr))
			return (list_clear(cmd_line_list_ptr, redi_list_ptr));
	}
	else
	{
		if (!case_redi(one_cmd_ptr, redi_list_ptr, redi_status))
			return (list_clear(cmd_line_list_ptr, redi_list_ptr));
	}
	return (1);
}
