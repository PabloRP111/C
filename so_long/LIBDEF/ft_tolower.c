/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:51:06 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 10:19:35 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ctype.h>
#include "libdef.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + 32;
	return (c);
}

/*
int	main(void)
{
	printf("%c",ft_tolower(97));
	printf("\n%c",tolower(97));
	return (0);
}*/