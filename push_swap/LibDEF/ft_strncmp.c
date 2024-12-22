/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:20:29 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 14:06:50 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	uc1;
	unsigned char	uc2;
	size_t			i;

	i = 0;
	while (s1[i] == s2[i] && i < n)
	{
		uc1 = (unsigned char)s1[i];
		uc2 = (unsigned char)s2[i];
		if (uc1 == '\0')
			return (0);
		i++;
	}
	if (s1[i] != s2[i] && i < n)
	{
		uc1 = (unsigned char)s1[i];
		uc2 = (unsigned char)s2[i];
		return (uc1 - uc2);
	}
	return (0);
}
