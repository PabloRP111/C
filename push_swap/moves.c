/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:40:32 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/23 09:12:43 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(struct s_lista **stack)
{
	struct s_lista	*temp_f;
	struct s_lista	*temp_s;

	if ((stack == NULL) || ((*stack) == NULL)
		|| (*stack)->next->n == (*stack)->n)
		return ;
	temp_s = (*stack)->next;
	temp_f = (*stack);
	temp_s->next->prev = temp_f;
	temp_s->prev = temp_f->prev;
	temp_f->next = temp_s->next;
	temp_f->prev->next = temp_s;
	temp_f->prev = temp_s;
	temp_s->next = temp_f;
	(*stack) = temp_s;
}

void	push(struct s_lista **stack_one, struct s_lista **stack_two)
{
	struct s_lista	*temp;

	if ((stack_two == NULL) || ((*stack_two) == NULL))
		return ;
	temp = (*stack_two);
	dis_node_list(&temp, stack_two);
	con_front_list(&temp, stack_one);
}

void	rotate(struct s_lista **stack)
{
	struct s_lista	*temp;

	if ((stack == NULL) || ((*stack) == NULL))
		return ;
	temp = (*stack)->next;
	(*stack) = temp;
}

void	reverse(struct s_lista **stack)
{
	struct s_lista	*temp;

	if ((stack == NULL) || ((*stack) == NULL))
		return ;
	temp = (*stack)->prev;
	(*stack) = temp;
}
