/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_errhandle2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 08:49:56 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/24 09:51:53 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

int	mem_err_redi(t_redi *redi)
{
	perr_and_init(0);
	free(redi);
	return (0);
}

int	mem_err_redi2(t_redi *redi)
{
	perr_and_init(0);
	free(redi->arg);
	free(redi);
	return (0);
}
