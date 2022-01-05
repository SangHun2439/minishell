/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:12:54 by jeson             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/01/05 11:45:47 by jeson            ###   ########.fr       */
=======
/*   Updated: 2022/01/03 11:33:26 by jeson            ###   ########.fr       */
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
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
<<<<<<< HEAD
		return (1);
=======
		return (0);
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
	}
	else
	{
		ft_putendl_fd(pwd, 1);
		free(pwd);
		return (0);
	}
}
