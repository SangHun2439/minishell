/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:16:56 by sangjeon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/01/04 20:03:49 by jeson            ###   ########.fr       */
=======
/*   Updated: 2022/01/03 16:19:54 by jeson            ###   ########.fr       */
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printf_prev_exit_status(void)
{
	char *s;

	s = ft_itoa(g_last_status);
	ft_putstr_fd(s, 1);
}

int	isecho_nopt(char *echoopt)
{
	int	i;

	if (ft_strlen(echoopt) < 2)
		return (0);
	if (ft_strncmp(echoopt, "-n", 2) != 0)
		return (0);
	i = 2;
	while (echoopt[i])
	{
		if (echoopt[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo_env(char *cmd_env)
{
	char *env_value;

	if (cmd_env[0] == '$' && cmd_env[1] == '?')
		printf_prev_exit_status();
	else
	{
		env_value = getenv(&cmd_env[1]);
		if (env_value)
			ft_putstr_fd(env_value, 1);
		else
			ft_putstr_fd(cmd_env, 1);
	}
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	res;

	i = 1;
	res = 0;
	while (cmd->argv[i] && isecho_nopt(cmd->argv[i]))
	{
		res = -1;
		i++;
	}
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '$')
			ft_echo_env(cmd->argv[i]);
		else
			ft_putstr_fd(cmd->argv[i], 1);
<<<<<<< HEAD
		if (cmd->argv[i + 1] != NULL)
=======
		if (cmd->argv[i] != NULL)
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
			ft_putstr_fd(" ", 1);
		++i;
	}
	if (res != -1)
		ft_putstr_fd("\n", 1);
	return (0);
}
