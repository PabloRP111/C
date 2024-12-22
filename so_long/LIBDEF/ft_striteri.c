/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 18:08:26 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 10:18:20 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	if (s != NULL || f != NULL)
	{
		while (s[i] != '\0')
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}
/*
int	main(void)
{
	char	*s;
	void 	(*f)(unsigned int, char*);

	ft_striteri(s ,&f);
	return (0);
}*/