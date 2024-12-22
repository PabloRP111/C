/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list_mult_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:23:56 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/24 14:36:50 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	val_args_mult2(char **argv, int i, int j)
{
	int	is_a_number;

	is_a_number = 0;
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
			if (ft_isalpha(argv[j][i]) == 1)
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

int	val_args_mult(char **argv)
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
	return (val_args_mult2(argv, 0, 1));
}

int	fill_list_mult_args(char **argv, struct s_lista **stack_a)
{
	int	j;

	j = 0;
	if (val_args_mult(argv) == 0 || val_nbrs(&(argv[1])) == 0)
		return (0);
	fill(stack_a, &(argv[1]), j);
	if (val_list(stack_a, list_len(stack_a), 0) == 0)
	{
		free_circular_list(stack_a);
		return (0);
	}
	get_index_r(stack_a, NULL, 1);
	return (1);
}
