/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:02:43 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/07 11:04:10 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	list_clear(t_list **cmd_line_list_ptr, t_list **redi_list_ptr)
{
	ft_lstclear(cmd_line_list_ptr, free);
	ft_lstclear(redi_list_ptr, del_redi_one);
	return (0);
}

int	is_quote(char c)
{
	if (c == '"')
		return (BIG_QUOTE);
	if (c == '\'')
		return (SMALL_QUOTE);
	return (0);
}

void	_free_split(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
}

void	perr_and_init(void)
{
	if (!errno)
		return ;
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	errno = 0;
}

int	is_closed_quote(char *str)
{
	int	res;

	res = is_quote(*str);
	if (!res)
		return (0);
	str++;
	while (*str && is_quote(*str) != res)
		str++;
	if (!*str)
		return (0);
	return (res);
}
