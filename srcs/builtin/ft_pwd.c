/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:12:54 by jeson             #+#    #+#             */
/*   Updated: 2022/01/05 11:45:47 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 256);
	if (!pwd)
	{
		ft_putendl_fd("fail to get current directory", 1);
		return (1);
	}
	else
	{
		ft_putendl_fd(pwd, 1);
		free(pwd);
		return (0);
	}
}
