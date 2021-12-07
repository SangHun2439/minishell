/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:50:39 by jeson             #+#    #+#             */
/*   Updated: 2021/12/04 14:44:48 by jeson            ###   ########.fr       */
=======
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 11:50:39 by jeson             #+#    #+#             */
/*   Updated: 2021/12/05 00:31:24 by sangjeon         ###   ########.fr       */
>>>>>>> d0be41d19b7c86389030dd8329984bf1e9351410
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * printf_prev_exit_status - $? 값 입력시
 * 이전에 실행된 명령어의 상태값 출력
 * 0이면 정상실행된 이전 명령어
 * 오류발생시 오류값이 출력
 * 어케함.... ㅠㅠ
 */

void	printf_prev_exit_status(void)
{
	ft_putstr_fd();
}

static int	isecho_nopt(char *flg)
{
	int	i;
	if (ft_strncmp(flg, "-n", 2) != 0)
		return (FALSE);
	i = 2;
	while (flg[i])
	{
		if (flg[i] != 'n')
			return (FALSE);
		++i;
	}
	return (TRUE);
}

char	find_env(char *tmp, char **envs)
{
	int	i;

	i = 0;
	while (envs[i])
	{
		if (!ft_strncmp(envs[i], tmp, ft_strlen(tmp)))
			return (envs[i] + ft_strlen[tmp] + 1);
	}
	return ("");
}

void	ft_echo_env(char **cmd, char **envs, int i)
{
	char *env_value;

	if (cmd[i][0] == '$' && cmd[i][1] == '?')
		printf_prev_exit_status();
	env_value = find_env(&(cmd[i][1]), envs);
	ft_putstr_fd(env_value, STDOUT);
}

void	ft_echo(char **cmd, char **envs)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (isecho_nopt(cmd[i]))
	{
		res = -1;
		++i;
	}
	while (cmd[i])
	{
		if (cmd[i][0] == '$')
			ft_echo_env(cmd, envs, i);
		else
			ft_putstr_fd(cmd[i], STDOUT);
		if (cmd[i + 1] != NULL)
			ft_putstr_fd(' ', STDOUT);
		++i;
	}
	if (res != -1)
		ft_putstr_fd('\n', STDOUT);
}
