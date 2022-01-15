/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:01:43 by jeson             #+#    #+#             */
/*   Updated: 2022/01/15 20:17:38 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd)
{
	char	**envs;
	int		i;

	if (cmd->argv[1])
	{
		ft_putendl_fd("env with no options or arguments", STDERR_FILENO);
		return (1);
	}
	envs = *cmd->env_ptr;
	i = -1;
	while (envs[++i])
		printf("%s\n", envs[i]);
	return (0);
}
