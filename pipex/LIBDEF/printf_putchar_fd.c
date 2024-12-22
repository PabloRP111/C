/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_putchar_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:46:46 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/29 14:03:43 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

void	printf_putchar_fd(char c, int fd, int *nchars)
{
	if (write(fd, &c, 1) != -1)
		*nchars += 1;
	else
		*nchars = -1;
}
