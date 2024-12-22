/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:30:16 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/31 19:55:55 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"	

void	think_move(struct s_lista **stack_a, struct s_lista **stack_b,
		int low_cost_index)
{
	struct s_lista	*temp;
	int				n_rotate_b;
	int				n_rotate_a;

	temp = (*stack_b);
	while (temp->index != low_cost_index)
		temp = temp->next;
	n_rotate_a = temp->enter_cos;
	n_rotate_b = temp->exit_cos;
	while (n_rotate_a != 0 || n_rotate_b != 0)
		manage_rotate(stack_a, stack_b, &n_rotate_b, &n_rotate_a);
	makem_sl(stack_a, stack_b, "pa");
}

void	calc_total_cost(struct s_lista **pos)
{
	int	exit_c_sign;
	int	enter_c_sign;

	if ((*pos)->exit_cos >= 0)
		exit_c_sign = 1;
	else
		exit_c_sign = -1;
	if ((*pos)->enter_cos >= 0)
		enter_c_sign = 1;
	else
		enter_c_sign = -1;
	if (enter_c_sign + exit_c_sign == 0)
		(*pos)->total_cos = abs((*pos)->enter_cos) + abs((*pos)->exit_cos);
	else
	{
		if (abs((*pos)->enter_cos) >= abs((*pos)->exit_cos))
			(*pos)->total_cos = abs((*pos)->enter_cos);
		else
			(*pos)->total_cos = abs((*pos)->exit_cos);
	}
}

void	choose_move(struct s_lista **stack_a, struct s_lista **stack_b)
{
	struct s_lista	*temp;
	int				len_b;
	int				low_cost_index;
	int				low_cost;

	len_b = list_len(stack_b);
	temp = (*stack_b)->next;
	calc_costs(stack_a, stack_b, len_b, 0);
	calc_total_cost(stack_b);
	low_cost = (*stack_b)->total_cos;
	low_cost_index = (*stack_b)->index;
	while (temp != (*stack_b))
	{
		calc_total_cost(&temp);
		if (low_cost > temp->total_cos)
		{
			low_cost = temp->total_cos;
			low_cost_index = temp->index;
		}
		temp = temp->next;
	}
	think_move(stack_a, stack_b, low_cost_index);
}
