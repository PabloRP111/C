/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_five.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:52:28 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/31 18:37:52 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_push_short(struct s_lista **stack_a, struct s_lista **stack_b,
		int max, int min)
{
	if (((*stack_b)->index > max || (*stack_b)->index < min)
		&& (*stack_a)->index == min)
		makem_sl(stack_a, stack_b, "pa");
	else if ((*stack_a)->index != min
		&& ((*stack_b)->index > (*stack_a)->prev->index
			&& ((*stack_b)->index < (*stack_a)->index)))
		makem_sl(stack_a, stack_b, "pa");
	else if (((*stack_b)->next->index > (*stack_a)->prev->index
			&& (*stack_b)->next->index < (*stack_a)->index))
	{
		makem_sl(stack_a, stack_b, "sb");
		makem_sl(stack_a, stack_b, "pa");
	}
	else
		return (0);
	if (is_ordered(stack_a, stack_b, list_len(stack_a)) != 1)
		makem_sl(stack_a, stack_b, "ra");
	return (1);
}

void	check_swap_short(struct s_lista **stack_a, struct s_lista **stack_b,
		int *np)
{
	if ((*stack_a)->seq == -1 || (*stack_a)->next->seq == -1)
	{
		if ((*stack_a)->next->index == (*stack_a)->index - 1
			&& ((*stack_b) != NULL && (*stack_b)->next->index
				== (*stack_b)->index - 1) && list_len(stack_a) > 2)
		{
			makem_sl(stack_a, stack_b, "ss");
			(*stack_a)->seq = -1;
			(*stack_a)->next->seq = -1;
			*np = 0;
		}
		else if (((*stack_a)->next->index == (*stack_a)->index - 1)
			&& list_len(stack_a) > 2)
		{
			makem_sl(stack_a, stack_b, "sa");
			(*stack_a)->seq = -1;
			(*stack_a)->next->seq = -1;
			*np = 0;
		}
	}
	if ((*stack_b) != NULL && (*stack_b)->next->index
		== (*stack_b)->index - 1)
		makem_sl(stack_a, stack_b, "sb");
}

void	isolate_five(struct s_lista **stack_a, struct s_lista **stack_b,
		int len, int np)
{
	int	max;
	int	min;

	get_sequences(stack_a);
	while (len-- > 0)
	{
		get_max_and_min(stack_a, &max, &min);
		check_swap_short(stack_a, stack_b, &np);
		if ((*stack_a)->seq != -1 && !(len == 0 && (*stack_a)->index == min)
			&& is_ordered_five(stack_a, min, list_len(stack_a)) == 0)
		{
			makem_sl(stack_a, stack_b, "pb");
			np = 1;
		}
		else if (stack_b != NULL && (*stack_b) != NULL && np != 1
			&& ((*stack_a)->prev->seq == -1 || (*stack_a)->seq == -1)
			&& check_push_short(stack_a, stack_b, max, min) == 1)
			len++;
		else if (!(len == 0 && (*stack_a)->index == min))
		{
			makem_sl(stack_a, stack_b, "ra");
			np = 0;
		}
	}
}

void	short_five(struct s_lista **stack_a, struct s_lista **stack_b,
		int len)
{
	if (is_ordered(stack_a, stack_b, len) != 1)
		isolate_five(stack_a, stack_b, len, 0);
	while (is_ordered(stack_a, stack_b, len) != 1
		&& (stack_b != NULL && (*stack_b) != NULL))
		choose_move(stack_a, stack_b);
}
