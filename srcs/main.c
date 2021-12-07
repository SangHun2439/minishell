/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:59:57 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/05 11:46:04 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	/* 리다이렉션이나 파이프가 걸리면 여러개의 명령어를 처리해야해서
	리스트로 명령어들을 구현 */
	t_list	*cmd_list;

	if (argc != 1)
		return (0);
	(void)argv;
	cmd_list = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		line = rl_gets();
		parse_cmd(&cmd_list, line);
		// 입력된 명령어에 따라 실행
		ft_lstiter(cmd_list, print_cmd_info);
		ft_lstclear(&cmd_list, del_cmd);
	}
}
