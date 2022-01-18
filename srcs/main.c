/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:59:57 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/18 12:47:54 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char		*line;
	t_list		*cmd_list;
	extern char	**environ;
	char		**my_environ;
	int			parse_status;

	if (argc != 1)
		return (0);
	init(argv, &cmd_list, environ, &my_environ);
	environ = my_environ;
	while (1)
	{
		line = rl_gets();
		parse_status = parse_cmd(&cmd_list, line, &environ);
		if (parse_status != EMPTYLINE)
			g_vars.last_status = parse_status;
		if (parse_status == 0)
			g_vars.last_status = exec_cmd(cmd_list);
		ft_lstclear(&cmd_list, del_cmd);
	}
}
