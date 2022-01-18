/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:11:36 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/18 16:42:26 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
