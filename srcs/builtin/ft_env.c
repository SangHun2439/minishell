/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:01:43 by jeson             #+#    #+#             */
/*   Updated: 2021/12/06 17:42:12 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
 * env 값을 배열로 가져올때
 */
int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		write(STDOUT, env[i], ft_strlen(env[i]));
		write(STDOUT, '\n', 1);
		++i;
	}
	return (TRUE);
}

/*
 * env 값을 리스트로 가져올때
 * env 는 local 값을 가져가는 방향으로 구성
 */

typedef struct s_cmd
{
	char	**argv;
	char	multi_status;
	t_envs	*envs;
}

typedef struct s_envs
{
	char	*key;
	char	*value;
	struct	s_envs *next;
}	t_envs


int	ft_env(t_cmd *cmd)
{
	t_envs	*tmp_node;

	tmp_node = cmd->envs;
	while (tmp_node)
	{
		ft_putstr_fd(tmp_node->key, STDOUT);
		ft_putstr_fd("=", STDOUT);
		ft_putendl_fd(tmp_node->value, STDOUT);
		tmp_node = tmp_node->next;
	}
	return (TRUE);
}
