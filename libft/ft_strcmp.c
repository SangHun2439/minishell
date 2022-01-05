/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeson <jeson@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 10:32:22 by jeson             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/01/05 13:51:58 by jeson            ###   ########.fr       */
=======
/*   Updated: 2022/01/03 15:45:54 by jeson            ###   ########.fr       */
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char c1;
	unsigned char c2;

	while (1)
	{
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2)
			return (1);
<<<<<<< HEAD
		if (!c1)
=======
		if (!c2)
>>>>>>> 2b92af95d14440155de3e5e750fa73c8572eb48b
			break ;
	}
	return (0);
}
