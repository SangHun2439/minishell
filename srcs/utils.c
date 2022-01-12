/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:11:36 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/12 21:50:51 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redi_info(void *content)
{
	t_redi	*redi;
	char	*str;

	redi = content;
	str = "normal";
	if (redi->redi_status == REDIRECT_INPUT)
		str = "input";
	if (redi->redi_status == REDIRECT_OUTPUT)
		str = "output";
	if (redi->redi_status == REDIRECT_APPEND)
		str = "append";
	if (redi->redi_status == REDIRECT_HEREDOC)
		str = "heredoc";
	printf("redi_status : %s\n", str);
	printf("redi_arg : %s\n", redi->arg);
}

void	print_cmd_info(void *content)
{
	t_cmd	*cmd;
	char	**arr;
	// char	**env;

	cmd = content;
	arr = cmd->argv;
	printf("=== cmd ===\n");
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
	printf("--- redi ---\n");
	ft_lstiter(cmd->redi_list, print_redi_info);
}

void	free_split(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
}

char	*ft_strndup(const char *s1, size_t max)
{
	char	*res;
	size_t	i;

	res = (char *)malloc(sizeof(char) * (max + 1));
	if (!res)
		return (0);
	i = 0;
	while (s1[i] && i < max)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
