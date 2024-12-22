/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:45:49 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 10:17:13 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

void	ft_lstadd_back(t_list **lst, t_list *new_n)
{
	t_list	*last;

	if (!lst || !new_n)
		return ;
	if (!*lst)
	{
		*lst = new_n;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new_n;
}

/*
int main(void)
{
	t_list	*lst = ft_lstnew("Hello");
	ft_lstadd_front(&lst, ft_lstnew("Hola"));
	ft_lstadd_back(&lst, ft_lstnew("Bonjour"));
	printf("%s\n", lst->content);
	printf("%s\n", ft_lstlast(lst)->content);
	printf("%s\n", lst->next->content);
	return (0);
}*/