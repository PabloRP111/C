/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:26:13 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 10:17:23 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdef.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(del)(lst->content);
	free(lst);
}

/*
void free_data(void *content) {
    if (content != 0) {
        free(content);
    }
}

int main() {
	char *numb = malloc(sizeof(char *) * 3);
	ft_strlcpy(numb, "42", 2);
    t_list *lst = ft_lstnew(numb);

    printf("Contenido de lst antes de eliminar: %s\n", (char*)lst->content);

    if (lst == NULL) {
        printf("La lista está vacía.\n");
    } else {
        ft_lstdelone(lst, free_data);
        printf("lst después de eliminar: %s\n", (char*)lst->content);
    }

    return 0;
}
*/