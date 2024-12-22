/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:25:41 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 10:16:35 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	else
		ft_memset(ptr, 0, count * size);
	return (ptr);
}

/*
int main (void)
{
    int i = 5;
    int *array = (int *)ft_calloc(i, sizeof(int));
    int *array2 = (int *)calloc(i, sizeof(int));

    printf("%p %s", array, (char *) array);
    printf("\n%p %s", array2, (char *) array2);

    return (0);
}*/
