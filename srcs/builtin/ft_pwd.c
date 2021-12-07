/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:12:54 by jeson             #+#    #+#             */
/*   Updated: 2021/12/06 17:44:20 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, PWD_BUF_SIZE);
	if (!pwd)
	{
		ft_putendl_fd("fail to get current directory", STDOUT);
		return (FALSE);
	}
	else
	{
		ft_putendl_fd(pwd, STDOUT);
		free(pwd);
		return (TRUE);
	}
}
