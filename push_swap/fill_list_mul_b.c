/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list_mul_b.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:23:56 by prosas-p          #+#    #+#             */
/*   Updated: 2024/06/07 07:43:30 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	fill_b(struct s_lista **stack_a, char **argv, int j)
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

void	get_index_r_b(struct s_lista **current, struct s_lista **old_min_node,
		int index)
{
	struct s_lista	*min_node;
	struct s_lista	*temp;

	if ((*current) == NULL)
		return ;
	if (index > list_len_b(current))
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
	get_index_r_b(&((*current)->next), old_min_node, index);
}

int	val_args_mult2_b(char **argv, int i, int j, int is_a_number)
{
	while (argv[j] != NULL)
	{
		is_a_number = 0;
		while (argv[j][i] != '\0')
		{
			if (ft_isdigit(argv[j][i]) == 1
			&& (argv[j][i + 1] == '-' || argv[j][i + 1] == '+'))
				return (0);
			if (ft_isdigit(argv[j][i]) == 1)
				is_a_number = 1;
			if (ft_isdigit(argv[j][i]) != 1 && argv[j][i] != '-'
				&& argv[j][i] != '+')
				return (0);
			if (argv[j][i] == ' ' && ft_isdigit(argv[j][i + 1]) == 1
				&& is_a_number == 1)
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (is_a_number);
}

int	val_args_mult_b(char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (argv[j] != NULL)
	{
		if (argv[j][0] == '\0')
			return (0);
		while (argv[j][i] != '\0')
		{
			if ((ft_isdigit(argv[j][i]) == 0) && argv[j][i] != ' ' &&
				(argv[j][i] != '-' && ft_isdigit(argv[j][i + 1]) == 0) &&
				(argv[j][i] != '+' && ft_isdigit(argv[j][i + 1]) == 0))
				return (0);
			if ((argv[j][i] == '-' || argv[j][i] == '+')
				&& (ft_isdigit(argv[j][i + 1]) == 0))
				return (0);
			i++;
		}
		i = 0;
		j++;
	}
	return (val_args_mult2_b(argv, 0, 1, 0));
}

int	fill_list_mult_b(char **argv, struct s_lista **stack_a)
{
	int	j;

	j = 0;
	if (val_args_mult_b(argv) == 0 || val_nbrs_b(&(argv[1])) == 0)
		return (0);
	fill_b(stack_a, &(argv[1]), j);
	if (val_list_b(stack_a, list_len_b(stack_a), 0) == 0)
	{
		free_circular_list_b(stack_a);
		return (0);
	}
	get_index_r_b(stack_a, NULL, 1);
	return (1);
}
