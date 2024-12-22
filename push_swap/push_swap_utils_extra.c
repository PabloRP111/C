/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 08:09:30 by prosas-p          #+#    #+#             */
/*   Updated: 2024/06/07 11:15:30 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	val_nbrs(char **nbrs)
{
	int		j;
	long	n;

	j = 0;
	while (nbrs[j] != NULL)
	{
		n = ft_atoi_swap((nbrs[j]));
		if (n > INT32_MAX || n < INT32_MIN)
			return (0);
		j++;
	}
	return (1);
}

void	con_front_list(struct s_lista **node, struct s_lista **stack)
{
	if (stack == NULL)
		return ;
	if ((*stack) != NULL)
	{
		(*node)->next = (*stack);
		(*node)->prev = (*stack)->prev;
		(*stack)->prev->next = (*node);
		(*stack)->prev = (*node);
		(*stack) = (*node);
	}
	else
	{
		(*node)->next = (*node);
		(*node)->prev = (*node);
		(*stack) = (*node);
	}
}

void	dis_node_list(struct s_lista **node, struct s_lista **stack)
{
	if (*node == NULL || stack == NULL || (*stack) == NULL)
		return ;
	else
	{
		if ((*node)->next->index != (*node)->index
			&& (*node)->prev->index != (*node)->index)
		{
			(*stack) = (*node)->next;
			(*node)->next->prev = (*node)->prev;
			(*node)->prev->next = (*node)->next;
			(*node)->next = NULL;
			(*node)->prev = NULL;
		}
		else
		{
			(*stack) = NULL;
			stack = NULL;
		}
	}
}

int	is_ordered(struct s_lista **stack_a, struct s_lista **stack_b, int len)
{
	struct s_lista	*temp;
	int				i;

	temp = (*stack_a)->next;
	i = (*stack_a)->index;
	while (temp != (*stack_a))
	{
		if (temp->index < i)
			i = temp->index;
		temp = temp->next;
	}
	if (i != 1 || (*stack_b) != NULL)
		return (0);
	while (temp->index != i)
		temp = temp->next;
	while (len-- > 0)
	{
		if (temp->index != i)
			return (0);
		i++;
		temp = temp->next;
	}
	return (1);
}

int	is_ordered_five(struct s_lista **stack_a, int min, int len)
{
	struct s_lista	*temp;
	int				max_index;

	temp = (*stack_a);
	while (temp->index != min)
		temp = temp->next;
	max_index = temp->index;
	while (len-- > 0)
	{
		if (temp->index > max_index)
			max_index = temp->index;
		else if (temp->index < max_index)
			return (0);
		temp = temp->next;
	}
	return (1);
}
