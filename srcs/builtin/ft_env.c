/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:01:43 by jeson             #+#    #+#             */
/*   Updated: 2022/01/03 12:40:52 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd *cmd)
{
	char **envs;

	envs = *(cmd->env_ptr);
	while (*envs)
		ft_putendl_fd(*envs++, 1);
	return (0);
}
