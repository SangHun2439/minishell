/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:59:16 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/28 00:35:32 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

int	case_cmd(char **one_cmd_ptr, t_list **cmd_line_list_ptr)
{
	char	*str;
	t_list	*new_lst;

	str = get_word_move_addr(one_cmd_ptr);
	if (!str)
		return (parse_err_mem());
	new_lst = ft_lstnew(str);
	if (!new_lst)
	{
		free(str);
		return (parse_err_mem());
	}
	ft_lstadd_back(cmd_line_list_ptr, new_lst);
	return (0);
}

int	case_redi(char **one_cmd_ptr, t_list **redi_list_ptr, int redi_status)
{
	t_redi	*redi;
	t_list	*new_lst;

	redi_move_ptr(one_cmd_ptr, redi_status);
	if (!**one_cmd_ptr || is_multi_cmd(*one_cmd_ptr))
		return (parse_unexpected_err(*one_cmd_ptr));
	redi = malloc(sizeof(t_redi));
	if (!redi)
		return (parse_err_mem());
	redi->redi_status = redi_status;
	redi->arg = get_word_move_addr(one_cmd_ptr);
	if (!redi->arg)
		return (mem_err_redi(redi));
	new_lst = ft_lstnew(redi);
	if (!new_lst)
		return (mem_err_redi2(redi));
	ft_lstadd_back(redi_list_ptr, new_lst);
	return (0);
}

int	init_cmd(t_list *cmd_line_list, t_list *redi_list, char ***env_ptr, \
t_cmd **cmd_ptr)
{
	t_list	*lst;

	if (!cmd_line_list && !redi_list)
		return (parse_unexpected_err2());
	*cmd_ptr = (t_cmd *)malloc(sizeof(t_cmd));
	if (!*cmd_ptr)
		return (EMEMLACK);
	(*cmd_ptr)->argv = list_to_arr(cmd_line_list);
	while (cmd_line_list)
	{
		lst = cmd_line_list;
		cmd_line_list = cmd_line_list->next;
		free(lst);
	}
	if (!(*cmd_ptr)->argv)
	{
		free(*cmd_ptr);
		list_clear(&cmd_line_list, &redi_list);
		return (EMEMLACK);
	}
	(*cmd_ptr)->redi_list = redi_list;
	(*cmd_ptr)->env_ptr = env_ptr;
	return (0);
}

int	parse_one_cmd(char *one_cmd, char ***env_ptr, t_cmd **cmd_ptr)
{
	t_list	*cmd_line_list;
	t_list	*redi_list;
	int		res;

	cmd_line_list = 0;
	redi_list = 0;
	res = 0;
	while (*one_cmd)
	{
		if (!_isspace(*one_cmd))
		{
			res = fill_cmd_redi_list(&one_cmd, &cmd_line_list, &redi_list);
			if (res != 0)
				return (res);
		}
		else
			one_cmd++;
	}
	return (init_cmd(cmd_line_list, redi_list, env_ptr, cmd_ptr));
}

int	parse_cmd(t_list **cmd_list_ptr, char *line, char ***env_ptr)
{
	char	**cmd_arr;
	int		i;
	t_cmd	*cmd;
	t_list	*new_lst;
	int		res;

	res = parse_init(&line, &cmd_arr);
	if (res != 0)
		return (res);
	i = 0;
	while (cmd_arr[i])
	{
		res = parse_one_cmd(cmd_arr[i], env_ptr, &cmd);
		if (res != 0)
			return (parse_err_cmd(cmd_arr, res));
		new_lst = ft_lstnew(cmd);
		if (!new_lst)
			return (parse_err_mem2(cmd_arr, cmd));
		ft_lstadd_back(cmd_list_ptr, new_lst);
		i++;
	}
	_free_split(cmd_arr);
	return (0);
}
