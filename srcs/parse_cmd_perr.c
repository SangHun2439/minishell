/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_perr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:02:24 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/24 08:59:57 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

void	normal_err(void)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	errno = 0;
}

void	parse_err(char *info)
{
	ft_putstr_fd("parse error ", STDERR_FILENO);
	if (info)
	{
		ft_putstr_fd("near ", STDERR_FILENO);
		ft_putstr_fd(info, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	errno = 0;
}

void	perr_and_init(char *info)
{
	if (!errno)
		return ;
	if (errno == EPARSE)
		return (parse_err(info));
	if (errno)
		return (normal_err());
}
