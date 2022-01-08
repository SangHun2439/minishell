/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:12:54 by jeson             #+#    #+#             */
/*   Updated: 2022/01/08 16:58:52 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 256);
	if (!pwd)
		return (1);
	else
		printf("%s\n", pwd);
	free(pwd);
	return (0);
}
