/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:43:15 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/16 09:46:12 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	makem_tl(struct s_lista **stack_a, struct s_lista **stack_b,
		char *move)
{
	if (ft_strncmp(move, "rra", 4) == '\0')
		reverse(stack_a);
	else if (ft_strncmp(move, "rrb", 4) == '\0')
		reverse(stack_b);
	else if (ft_strncmp(move, "rrr", 4) == '\0')
	{
		reverse(stack_a);
		reverse(stack_b);
	}
	else
		ft_printf("\n?\n");
}

void	makem_sl(struct s_lista **stack_a, struct s_lista **stack_b,
		char *move)
{
	if (ft_strncmp(move, "sa", 3) == '\0')
		swap(stack_a);
	else if (ft_strncmp(move, "sb", 3) == '\0')
		swap(stack_b);
	else if (ft_strncmp(move, "ss", 3) == '\0')
	{
		swap(stack_a);
		swap(stack_b);
	}
	else if (ft_strncmp(move, "pa", 3) == '\0')
		push(stack_a, stack_b);
	else if (ft_strncmp(move, "pb", 3) == '\0')
		push(stack_b, stack_a);
	else if (ft_strncmp(move, "ra", 3) == '\0')
		rotate(stack_a);
	else if (ft_strncmp(move, "rb", 3) == '\0')
		rotate(stack_b);
	else if (ft_strncmp(move, "rr", 3) == '\0')
	{
		rotate(stack_a);
		rotate(stack_b);
	}
	else
		makem_tl(stack_a, stack_b, move);
	ft_printf("%s\n", move);
}
