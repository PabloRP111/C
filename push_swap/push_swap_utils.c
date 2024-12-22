/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 12:02:29 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/24 14:17:45 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	list_len(struct s_lista **stack)
{
	struct s_lista	*temp_a;
	int				len;
	int				n;

	if (stack == NULL || *stack == NULL)
		return (0);
	len = 1;
	n = (*stack)->n;
	temp_a = (*stack)->next;
	while (temp_a && temp_a->n != n)
	{
		len++;
		temp_a = temp_a->next;
	}
	return (len);
}

void	print_list(struct s_lista **stack)
{
	struct s_lista	*temp_a;
	int				len;
	int				i;

	if (stack == NULL || (*stack) == NULL)
		return ;
	i = 0;
	temp_a = (*stack);
	len = list_len(stack);
	while (i < len)
	{
		printf("%3d | %4d | %4d | %4d | %4d | %5d | %5d | %3d\n",
			temp_a->n, temp_a->index, temp_a->prev->n, temp_a->next->n,
			temp_a->seq, temp_a->enter_cos, temp_a->exit_cos,
			temp_a->total_cos);
		temp_a = temp_a->next;
		*stack = temp_a;
		i++;
	}
}

int	val_list(struct s_lista **stack_a, int len, int index)
{
	struct s_lista	*temp_a;
	int				nbool;

	nbool = 0;
	temp_a = (*stack_a)->next;
	while (temp_a != (*stack_a))
	{
		if (temp_a->n == (*stack_a)->n)
			return (0);
		temp_a = temp_a->next;
	}
	if (index < len)
		nbool = val_list(&(*stack_a)->next, len, index + 1);
	if (index >= len)
		nbool = 1;
	return (nbool);
}

void	free_circular_list(struct s_lista **stack)
{
	struct s_lista	*tmp;
	struct s_lista	*del;

	if (!stack || !(*stack))
		return ;
	tmp = (*stack)->next;
	del = (*stack)->next;
	while (tmp != (*stack))
	{
		tmp = tmp->next;
		free(del);
		del = tmp;
	}
	free(*stack);
	*stack = NULL;
}

long	ft_atoi_swap(const char *str)
{
	long	num;
	int		i;
	int		sign;

	if (str == NULL)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
		if (num > 2147483647 || num < -2147483648)
			return (num * sign);
	}
	return (num * sign);
}
