/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 20:08:08 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/07 11:17:41 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_move_addr(char **str_ptr, int quote_flag)
{
	char	*res;

	res = *str_ptr;
	while (*res && quote_flag != is_quote(*res))
		res++;
	if (*res)
		*str_ptr = res + 1;
}

char	*get_word_move_addr(char **str_ptr)
{
	char	*tmp;
	char	*word;
	int		i;
	int		quote_flag;

	tmp = *str_ptr;
	while (**str_ptr && !_isspace(**str_ptr) && !is_redi(*str_ptr))
	{
		quote_flag = is_quote(**str_ptr);
		if (quote_flag)
		{
			(*str_ptr)++;
			quote_move_addr(str_ptr, quote_flag);
		}
		else
			(*str_ptr)++;
	}
	word = malloc(sizeof(char) * (*str_ptr - tmp + 1));
	if (!word)
		return (0);
	i = 0;
	while (tmp != *str_ptr)
		word[i++] = *tmp++;
	word[i] = 0;
	return (word);
}

// char	*str_convert_env(char *str)
// {
// 	int		quote_flag;
// 	int		len;
// 	char	*res;
// 	char	*tmp;

// 	return (0);
// 	while (*str)
// 	{
// 		quote_flag = is_closed_quote(*str);
// 		if (quote_flag == SMALL_QUOTE)
// 			;
// 	}
// }

// int	dollar_handle(t_list *cmd_line_list, t_list *redi_list)
// {
// 	char	str;

// 	while (cmd_line_list)
// 	{
// 		str = str_convert_env(cmd_line_list->content);
// 		if (!str)
// 			return (EMEMLACK);
// 		free(cmd_line_list->content);
// 		cmd_line_list->content = str;
// 		cmd_line_list = cmd_line_list->next;
// 	}
// 	while (redi_list)
// 	{
// 		str = str_convert_env(((t_redi *)(redi_list->content))->arg);
// 		if (!str)
// 			return (EMEMLACK);
// 		free(((t_redi *)(redi_list->content))->arg);
// 		((t_redi *)(redi_list->content))->arg = str;
// 		redi_list = redi_list->next;
// 	}
// }
