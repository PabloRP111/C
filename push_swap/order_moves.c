/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 08:34:21 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/31 18:32:18 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	mark_lseq(struct s_lista **stack_a, int len)
{
	struct s_lista	*temp;
	int				lseq;
	int				aux_len;

	lseq = 0;
	temp = (*stack_a)->prev;
	aux_len = len;
	while (aux_len-- > 0)
	{
		if (temp->seq > lseq)
			lseq = temp->seq;
		temp = temp->prev;
	}
	while (len-- > 0 && lseq >= 0)
	{
		if (temp->seq == lseq)
		{
			lseq--;
			temp->seq = -1;
		}
		temp = temp->prev;
	}
}

void	get_sequences(struct s_lista **stack)
{
	struct s_lista	*cur;
	struct s_lista	*temp;

	temp = (*stack)->next;
	(*stack)->seq = 0;
	while (temp != (*stack))
	{
		cur = (*stack);
		temp->seq = 0;
		while (cur->index != temp->index)
		{
			if (temp->index > cur->index && temp->seq <= cur->seq)
				temp->seq++;
			cur = cur->next;
		}
		temp = temp->next;
	}
	mark_lseq(stack, list_len(stack));
}

void	check_swap(struct s_lista **stack_a, struct s_lista **stack_b,
	struct s_lista **temp, int *len)
{
	(*temp) = (*temp)->next;
	if ((*stack_a)->next->index == (*stack_a)->index - 1
		&& ((*stack_b) != NULL && (*stack_b)->next->index
			== (*stack_b)->index - 1) && list_len(stack_a) > 2)
		makem_sl(stack_a, stack_b, "ss");
	else if (((*stack_a)->next->index == (*stack_a)->index - 1)
		&& list_len(stack_a) > 2)
		makem_sl(stack_a, stack_b, "sa");
	else if ((*stack_b) != NULL && (*stack_b)->next->index
		== (*stack_b)->index - 1)
	{
		(*temp) = (*temp)->prev;
		makem_sl(stack_a, stack_b, "sb");
		*len += 1;
		return ;
	}
	else
	{
		(*temp) = (*temp)->prev;
		return ;
	}
	*len += 1;
}

void	isolate_seq(struct s_lista **stack_a, struct s_lista **stack_b, int len)
{
	struct s_lista	*temp;

	temp = (*stack_a);
	while (len-- > 0)
	{
		if ((temp->next->index == temp->index - 1 && (temp->seq == -1
					|| temp->next->seq == -1)) || ((*stack_b) != NULL
				&& (*stack_b)->next->index == (*stack_b)->index - 1))
			check_swap(stack_a, stack_b, &temp, &len);
		else if (temp->seq != -1)
		{
			temp = temp->next;
			makem_sl(stack_a, stack_b, "pb");
		}
		else if (!(len == -1 && (*stack_a)->index == 1))
		{
			temp = temp->next;
			makem_sl(stack_a, stack_b, "ra");
		}
	}
}

void	order(struct s_lista **stack_a, struct s_lista **stack_b)
{
	int				len;

	len = list_len(stack_a);
	get_sequences(stack_a);
	if (is_ordered(stack_a, stack_b, len) != 1)
		isolate_seq(stack_a, stack_b, len);
	while (is_ordered(stack_a, stack_b, len) != 1
		&& (stack_b != NULL && (*stack_b) != NULL))
		choose_move(stack_a, stack_b);
}
