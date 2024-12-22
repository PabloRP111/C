/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_costs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:20:37 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/31 18:31:12 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	calc_dist(struct s_lista **stack_a, struct s_lista **temp, int pos)
{
	int	dist_front;
	int	dist_back;

	dist_front = 0;
	dist_back = 1;
	while ((*temp)->index != pos)
	{
		(*temp) = (*temp)->next;
		dist_front++;
	}
	(*temp) = (*stack_a)->prev;
	while ((*temp)->index != pos)
	{
		(*temp) = (*temp)->prev;
		dist_back++;
	}
	if (dist_front <= dist_back)
		return (dist_front);
	else
		return (dist_back * -1);
	return (dist_front);
}

void	get_max_and_min(struct s_lista **stack_a, int *max_n, int *min_n)
{
	struct s_lista	*temp;

	temp = (*stack_a)->next;
	if (max_n != NULL)
		*max_n = (*stack_a)->index;
	if (min_n != NULL)
		*min_n = (*stack_a)->index;
	while (temp != (*stack_a))
	{
		if (max_n != NULL && *max_n < temp->index)
			*max_n = temp->index;
		if (min_n != NULL && *min_n > temp->index)
			*min_n = temp->index;
		temp = temp->next;
	}
}

int	calc_especial_case(struct s_lista **stack_a, int len_a)
{
	struct s_lista	*temp;
	int				min_n;
	int				i;

	i = -1;
	temp = (*stack_a);
	get_max_and_min(stack_a, NULL, &min_n);
	while (++i <= len_a / 2 && temp->index != min_n)
		temp = temp->next;
	if (temp->index == min_n)
		return (i);
	temp = (*stack_a)->prev;
	len_a -= i;
	i = 0;
	while (++i < len_a && temp->index != min_n)
		temp = temp->prev;
	if (temp->index == min_n)
		return ((i * -1));
	return (0);
}

int	calc_enter_cost(struct s_lista **stack_a, int cur_index, int max_i,
		int min_i)
{
	struct s_lista	*temp;
	int				i;
	int				len_a;
	int				pos;

	i = -1;
	len_a = list_len(stack_a);
	temp = (*stack_a);
	if (cur_index < min_i || cur_index > max_i)
		return (calc_especial_case(stack_a, len_a));
	while (!(temp->index > cur_index && temp->prev->index < cur_index))
		temp = temp->next;
	pos = temp->index;
	temp = (*stack_a);
	return (calc_dist(stack_a, &temp, pos));
}

void	calc_costs(struct s_lista **stack_a, struct s_lista **stack_b,
		int len_b, int distance)
{
	struct s_lista	*temp_b;
	int				half;
	int				max_i;
	int				min_i;

	temp_b = (*stack_b);
	half = len_b / 2;
	distance = 0;
	get_max_and_min(stack_a, &max_i, &min_i);
	while (len_b-- >= half && len_b >= 0)
	{
		temp_b->exit_cos = distance++;
		temp_b->enter_cos = calc_enter_cost(stack_a, temp_b->index, max_i,
				min_i);
		temp_b = temp_b->next;
	}
	distance = 0;
	temp_b = (*stack_b)->prev;
	while (len_b-- >= 0)
	{
		temp_b->exit_cos = --distance;
		temp_b->enter_cos = calc_enter_cost(stack_a, temp_b->index, max_i,
				min_i);
		temp_b = temp_b->prev;
	}
}
