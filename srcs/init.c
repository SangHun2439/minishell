/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:11:45 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/13 17:51:48 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_cpy(char **src)
{
	char	**res;
	int		env_cnt;
	int		len;
	int		i;

	env_cnt = 0;
	while (src[env_cnt])
		env_cnt++;
	res = (char **)malloc(sizeof(char *) * (env_cnt + 1));
	if (!res)
		return (init_err());
	i = 0;
	while (i < env_cnt)
	{
		len = ft_strlen(src[i]);
		res[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!res[i])
			return (init_err());
		res[i] = ft_memcpy(res[i], src[i], len + 1);
		i++;
	}
	res[env_cnt] = 0;
	return (res);
}

int	init(char **argv, t_list **cmd_list_ptr, char **environ, char ***my_environ)
{
	(void)argv;
	*cmd_list_ptr = 0;
	g_last_status = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	*my_environ = env_cpy(environ);
	return (0);
}
