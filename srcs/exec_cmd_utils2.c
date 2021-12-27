/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 23:30:20 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/28 00:52:45 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_cmd.h"

void	exec_perr_and_init(void)
{
	if (!errno)
		return ;
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	errno = 0;
}

void	exec_free_split(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
}
