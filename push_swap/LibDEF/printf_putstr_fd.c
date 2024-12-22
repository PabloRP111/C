/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putstr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:14:32 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 11:43:24 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

void	printf_putstr_fd(char *s, int fd, int *nchars)
{
	if (s != NULL)
	{
		if (write(fd, s, ft_strlen(s)) != -1)
			*nchars += ft_strlen(s);
		else
			*nchars = -1;
	}
	else
	{
		if (write(fd, "(null)", 6) != -1)
			*nchars += 6;
		else
			*nchars = -1;
	}
}
