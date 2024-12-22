/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:11:23 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/18 21:32:24 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	oposite_rotate_two(struct s_lista **stack_a, struct s_lista **stack_b,
		int *n_rotate_b, int *n_rotate_a)
{
	if (*n_rotate_a >= 0 && *n_rotate_b <= 0)
	{
		if (*n_rotate_a > 0)
		{
			(*n_rotate_a)--;
			makem_sl(stack_a, stack_b, "ra");
		}
		if (*n_rotate_b < 0)
		{
			makem_sl(stack_a, stack_b, "rrb");
			(*n_rotate_b)++;
		}
	}
}

void	oposite_rotate_one(struct s_lista **stack_a, struct s_lista **stack_b,
		int *n_rotate_b, int *n_rotate_a)
{
	if (*n_rotate_a <= 0 && *n_rotate_b >= 0)
	{
		if (*n_rotate_a < 0)
		{
			makem_sl(stack_a, stack_b, "rra");
			(*n_rotate_a)++;
		}
		if (*n_rotate_b > 0)
		{
			makem_sl(stack_a, stack_b, "rb");
			(*n_rotate_b)--;
		}
	}
}

void	positive_rotate(struct s_lista **stack_a, struct s_lista **stack_b,
		int *n_rotate_b, int *n_rotate_a)
{
	if (*n_rotate_a > 0 && *n_rotate_b > 0)
	{
		makem_sl(stack_a, stack_b, "rr");
		(*n_rotate_b)--;
		(*n_rotate_a)--;
	}
	else if (*n_rotate_a > 0 && *n_rotate_b == 0)
	{
		makem_sl(stack_a, stack_b, "ra");
		(*n_rotate_a)--;
	}
	else if (*n_rotate_a == 0 && *n_rotate_b > 0)
	{
		makem_sl(stack_a, stack_b, "rb");
		(*n_rotate_b)--;
	}
}

void	negative_rotate(struct s_lista **stack_a, struct s_lista **stack_b,
		int *n_rotate_b, int *n_rotate_a)
{
	if (*n_rotate_a < 0 && *n_rotate_b < 0)
	{
		makem_sl(stack_a, stack_b, "rrr");
		(*n_rotate_b)++;
		(*n_rotate_a)++;
	}
	else if (*n_rotate_a < 0 && *n_rotate_b == 0)
	{
		makem_sl(stack_a, stack_b, "rra");
		(*n_rotate_a)++;
	}
	else if (*n_rotate_a == 0 && *n_rotate_b < 0)
	{
		makem_sl(stack_a, stack_b, "rrb");
		(*n_rotate_b)++;
	}
}

void	manage_rotate(struct s_lista **stack_a, struct s_lista **stack_b,
		int *n_rotate_b, int *n_rotate_a)
{
	if (*n_rotate_a == 0 && *n_rotate_b == 0)
		return ;
	if (*n_rotate_a <= 0 && *n_rotate_b <= 0)
	{
		negative_rotate(stack_a, stack_b, n_rotate_b, n_rotate_a);
		return ;
	}
	if (*n_rotate_a >= 0 && *n_rotate_b >= 0)
	{
		positive_rotate(stack_a, stack_b, n_rotate_b, n_rotate_a);
		return ;
	}
	if (*n_rotate_a <= 0 && *n_rotate_b >= 0)
	{
		oposite_rotate_one(stack_a, stack_b, n_rotate_b, n_rotate_a);
		return ;
	}
	if (*n_rotate_a >= 0 && *n_rotate_b <= 0)
	{
		oposite_rotate_two(stack_a, stack_b, n_rotate_b, n_rotate_a);
		return ;
	}
}
