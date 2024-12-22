/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:51:07 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 10:17:07 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

int	ft_isprint(unsigned int n)
{
	int	nbool;

	nbool = 1;
	if (!(n >= 32 && n <= 126))
		nbool = 0;
	return (nbool);
}

/*
int	main(void)
{
	int n;

	n = 65;
	printf("%d", ft_isprint(n));
	printf("%d", isprint(n));
	return (0);
}*/
