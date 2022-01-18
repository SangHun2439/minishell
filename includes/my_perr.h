/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_perr.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:45:25 by sangjeon          #+#    #+#             */
/*   Updated: 2022/01/18 12:33:58 by jeson            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_PERR_H
# define MY_PERR_H

# include <errno.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

# define EUNEXPECTED 256
# define EUNCLOSED 257

void	put_errmsg(void);

#endif
