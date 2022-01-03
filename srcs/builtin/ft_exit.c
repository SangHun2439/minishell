/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:35:43 by jeson             #+#    #+#             */
/*   Updated: 2022/01/03 22:23:06 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_atol(const char *argv_ptr, int *flg_exit)
{
	int	sign;
	long long res;

	sign = 1;
	*flg_exit = 0;
	if (*argv_ptr == '-')
		sign = -1;
	if (*argv_ptr == '-' || *argv_ptr == '+')
		argv_ptr++;
	res = 0;
	while (*flg_exit != 1 && ft_isdigit(*argv_ptr))
	{
		res = res * 10 + (*argv_ptr++ - '0');
		if (sign == 1 && res >= LLONG_MAX / 10 && *argv_ptr > LLONG_MAX % 10 + '0')
			*flg_exit = 1;
		if (sign == -1 && res >= LLONG_MAX / 10 && *argv_ptr > LONG_MAX % 10 + '1')
			*flg_exit = 1;
	}
	/* LLONG_MAX 범위 밖의 값 or numeric이 아니면 echo $? 값이 255 고정*/
	if (*flg_exit || *argv_ptr != '\0')
	{
		*flg_exit = 1;
		return (255);
	}
	/* 해당 조건아닌 경우 sign * res 값 가지고
	 * 256으로 나눈 나머지가 echo $?로 표시됨*/
	return (sign * res);
}

int	ft_exit(t_cmd *cmd)
{
	long long exit_ret;
	int	i;
	int	flg_exit;

	i = 0;
	while (cmd->argv[i])
		i++;
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (i == 1)
		exit(g_last_status);
	exit_ret = ft_atol(cmd->argv[1], &flg_exit);
	if (flg_exit)
	{
		ft_putstr_fd("exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(exit_ret);
	}
	if (i > 2)
	{
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	exit (exit_ret % 256);
}
