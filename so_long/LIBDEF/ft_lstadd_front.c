/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:26:34 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 10:17:17 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

void	ft_lstadd_front(t_list **lst, t_list *new_n)
{
	if (!lst || !new_n)
		return ;
	new_n->next = *lst;
	*lst = new_n;
}
/*
int	main(void)
{
	t_list	*lst = ft_lstnew("Hello");
	ft_lstadd_front(&lst, ft_lstnew("Hola"));
	printf("%s\n", lst->next->content);
	return (0);
}*/