/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_moves_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:43:15 by prosas-p          #+#    #+#             */
/*   Updated: 2024/06/07 10:44:00 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	is_ordered(struct s_lista **stack_a, struct s_lista **stack_b)
{
	struct s_lista	*temp;
	int				index;

	temp = (*stack_a)->next;
	index = 1;
	if ((*stack_b) != NULL)
		return (0);
	while (temp != (*stack_a))
	{
		if (temp->n < temp->prev->n)
			return (0);
		temp = temp->next;
	}
	return (1);
}

void	con_front_list_b(struct s_lista **node, struct s_lista **stack)
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

void	dis_node_list_b(struct s_lista **node, struct s_lista **stack)
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

int	makem_tl_b(struct s_lista **stack_a, struct s_lista **stack_b,
		char *move)
{
	if (ft_strncmp(move, "pa", 2) == 0)
		push_b(stack_a, stack_b);
	else if (ft_strncmp(move, "rrb", 3) == 0)
		reverse_b(stack_b);
	else if (ft_strncmp(move, "rrr", 3) == 0)
	{
		reverse_b(stack_a);
		reverse_b(stack_b);
	}
	else if (ft_strncmp(move, "sb", 2) == 0)
		swap_b(stack_b);
	else if (ft_strncmp(move, "ss", 2) == 0)
	{
		swap_b(stack_a);
		swap_b(stack_b);
	}
	else if (ft_strncmp(move, "rb", 2) == 0)
		rotate_b(stack_b);
	else if (ft_strncmp(move, "rr", 2) == 0)
	{
		rotate_b(stack_a);
		rotate_b(stack_b);
	}
	return (1);
}

int	make_mb(struct s_lista **stack_a, struct s_lista **stack_b,
		char *move)
{
	if (ft_strncmp(move, "sa", 2) == 0)
		swap_b(stack_a);
	else if (ft_strncmp(move, "rra", 3) == 0)
		reverse_b(stack_a);
	else if (ft_strncmp(move, "ra", 2) == 0)
		rotate_b(stack_a);
	else if (ft_strncmp(move, "pb", 2) == 0)
		push_b(stack_b, stack_a);
	else
	{
		if ((*stack_b) != NULL)
			return (makem_tl_b(stack_a, stack_b, move));
		else if (move[0] != '\n')
			return (0);
	}
	return (1);
}
