/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 21:02:43 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/18 00:47:52 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cmd.h"

int	list_clear(t_list **cmd_line_list_ptr, t_list **redi_list_ptr)
{
	ft_lstclear(cmd_line_list_ptr, free);
	ft_lstclear(redi_list_ptr, del_redi_one);
	return (0);
}

void	skip_space(char **line_ptr)
{
	while (**line_ptr && _isspace(**line_ptr))
		(*line_ptr)++;
}

void	_free_split(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i])
		free(str_arr[i++]);
	free(str_arr);
}

int	fill_cmd_redi_list(char **one_cmd_ptr, \
t_list **cmd_line_list_ptr, t_list **redi_list_ptr)
{
	int		redi_status;

	redi_status = is_multi_cmd(*one_cmd_ptr);
	if (!redi_status)
	{
		if (!case_cmd(one_cmd_ptr, cmd_line_list_ptr))
			return (list_clear(cmd_line_list_ptr, redi_list_ptr));
	}
	else
	{
		if (!case_redi(one_cmd_ptr, redi_list_ptr, redi_status))
			return (list_clear(cmd_line_list_ptr, redi_list_ptr));
	}
	return (1);
}

char	*get_word_move_addr(char **str_ptr)
{
	char	*tmp;
	char	*word;
	int		i;

	tmp = *str_ptr;
	while (**str_ptr && !_isspace(**str_ptr) && !is_multi_cmd(*str_ptr))
		(*str_ptr)++;
	word = malloc(sizeof(char) * (*str_ptr - tmp + 1));
	if (!word)
		return (0);
	i = 0;
	while (tmp != *str_ptr)
		word[i++] = *tmp++;
	word[i] = 0;
	return (word);
}
