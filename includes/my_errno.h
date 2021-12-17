/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_errno.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sangjeon <sangjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:56:58 by sangjeon          #+#    #+#             */
/*   Updated: 2021/12/17 19:42:32 by sangjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_HANDLE_H
# define ERR_HANDLE_H

# include <errno.h>
# include <string.h>
# include "libft.h"

# define EPARSE 258

void	perr_and_init(void);

#endif
