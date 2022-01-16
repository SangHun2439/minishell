/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:59:57 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/16 22:39:46 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*line;
	/* 리다이렉션이나 파이프가 걸리면 여러개의 명령어를 처리해야해서
	리스트로 명령어들을 구현 */
	t_list	*cmd_list;
	extern char	**environ;
	char 		**my_environ;
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
			// ft_lstiter(cmd_list, print_cmd_info);
			// 입력된 명령어에 따라 실행
			g_vars.last_status = exec_cmd(cmd_list);
		// printf("%d\n", g_vars.last_status);
		ft_lstclear(&cmd_list, del_cmd);
	}
}
