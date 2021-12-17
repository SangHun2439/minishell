/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_errno.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 18:02:24 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/17 19:42:25 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_errno.h"

void	normal_err(void)
{
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	errno = 0;
}

void	parse_err(void)
{
	ft_putstr_fd("parse error\n", STDERR_FILENO);
	errno = 0;
}

void	perr_and_init(void)
{
	if (errno == EPARSE)
		return (parse_err());
	if (errno)
		return (normal_err());
}
