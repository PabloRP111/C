/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:16:13 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 10:17:42 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*pt;

	pt = (unsigned char *) str;
	while (n-- > 0)
	{
		if (*pt++ == (unsigned char) c)
			return ((void *) pt -1);
	}
	return (0);
}
/*
int main (void)
{
	char	str[]="1234567890 Esto es el número bytes";

	printf("%s", ft_memchr(str, 'E', sizeof(str)));
 	printf("\n%s", memchr(str, 'E', sizeof(str)));
	return (0);
}*/
