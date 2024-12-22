/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:47:49 by prosas-p          #+#    #+#             */
/*   Updated: 2024/09/19 14:20:01 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	go_to_begining(struct s_lista **stack_a, int len)
{
	struct s_lista	*temp;
	int				i;
	int				dist;

	temp = (*stack_a);
	i = -1;
	while (i++ <= len / 2 && temp->index != 1)
		temp = temp->next;
	temp = (*stack_a);
	dist = i;
	len -= i -1;
	i = -1;
	while (i++ < len && temp->index != 1)
		temp = temp->prev;
	if (dist <= i)
	{
		while (temp->index == 1 && (*stack_a)->index != 1)
			makem_sl(stack_a, NULL, "ra");
	}
	else
	{
		while (temp->index == 1 && (*stack_a)->index != 1)
			makem_sl(stack_a, NULL, "rra");
	}
}

void	short_num(struct s_lista **stack_a, struct s_lista **stack_b)
{
	int	len;

	len = list_len(stack_a);
	if (is_ordered(stack_a, stack_b, len) == 1)
		return ;
	if (len <= 3)
		makem_sl(stack_a, NULL, "sa");
	else
		short_five(stack_a, stack_b, len);
}

void	fill(struct s_lista **stack_a, char **argv, int j)
{
	struct s_lista	*new_node;
	struct s_lista	*temp;

	while (argv[j] != NULL)
	{
		new_node = (struct s_lista *)malloc(sizeof(struct s_lista));
		if (new_node == NULL)
			return ;
		new_node->n = ft_atoi(argv[j]);
		new_node->next = NULL;
		if (*stack_a == NULL)
			*stack_a = new_node;
		else
		{
			temp = *stack_a;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new_node;
			new_node->prev = temp;
		}
		j++;
	}
	temp = *stack_a;
	temp->prev = new_node;
	new_node->next = temp;
}

void	get_index_r(struct s_lista **current, struct s_lista **old_min_node,
		int index)
{
	struct s_lista	*min_node;
	struct s_lista	*temp;

	if ((*current) == NULL)
		return ;
	if (index > list_len(current))
		return ;
	min_node = (*current);
	temp = (*current)->next;
	while (temp != (*current))
	{
		if (old_min_node == NULL && temp->n < min_node->n)
			min_node = temp;
		else if (temp->n < min_node->n && temp->n > (*old_min_node)->n)
			min_node = temp;
		temp = temp->next;
	}
	if (old_min_node == NULL || (min_node->n > (*old_min_node)->n))
	{
		min_node->index = index;
		index++;
		old_min_node = &min_node;
	}
	get_index_r(&((*current)->next), old_min_node, index);
}

int	main(int argc, char **argv)
{
	struct s_lista	*stack_a;
	struct s_lista	*stack_b;
	int				berror;

	berror = 0;
	stack_a = NULL;
	stack_b = NULL;
	if (argc == 2)
		berror = fill_list(argv, &stack_a);
	else if (argc > 2)
		berror = fill_list_mult_args(argv, &stack_a);
	else if (argc == 1)
		return (0);
	if (berror == 0)
		write(2, "Error\n", 6);
	else
	{
		if (list_len(&stack_a) <= 5)
			short_num(&stack_a, &stack_b);
		else
			order(&stack_a, &stack_b);
		go_to_begining(&stack_a, list_len(&stack_a));
		free_circular_list(&stack_a);
		free_circular_list(&stack_b);
	}
}
