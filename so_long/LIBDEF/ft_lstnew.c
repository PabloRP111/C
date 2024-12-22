/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 13:38:02 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 10:17:35 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->content = content;
	new->next = NULL;
	return (new);
}

/*
int	main(void)
{
	t_list	*new;

	new = ft_lstnew("Hola");
	printf("%s\n", new->content);
	return (0);
}*/