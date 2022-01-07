/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_errhandle2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 08:49:56 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/07 09:23:51 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mem_err_redi(t_redi *redi)
{
	perr_and_init();
	free(redi);
	return (EMEMLACK);
}

int	mem_err_redi2(t_redi *redi)
{
	perr_and_init();
	free(redi->arg);
	free(redi);
	return (EMEMLACK);
}

int	parse_err_mem3(t_list **cmd_line_list, t_list **redi_list)
{
	perr_and_init();
	list_clear(cmd_line_list, redi_list);
	return (EMEMLACK);
}
