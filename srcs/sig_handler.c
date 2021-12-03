/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:55:32 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/03 14:35:46 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_handler.h"

void	sigint_handler(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(void)
{
	ft_putstr_fd("quit signal\n", 1);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		return (sigint_handler());
	if (sig == SIGQUIT)
		return (sigquit_handler());
}
