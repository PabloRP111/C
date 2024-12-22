/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 09:13:41 by prosas-p          #+#    #+#             */
/*   Updated: 2024/05/31 18:31:33 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	free_nbrs_b(char **nbrs)
{
	int	i;

	i = 0;
	while (nbrs[i] != NULL)
	{
		free(nbrs[i]);
		i++;
	}
	free(nbrs);
}

int	val_args2_b(char *argv, int i, int ther_is_a_number)
{
	while (argv[i] != '\0')
	{
		if (ft_isdigit(argv[i]) == 1
			&& (argv[i + 1] == '-' || argv[i + 1] == '+'))
			return (0);
		if (ft_isdigit(argv[i]) == 1)
			ther_is_a_number = 1;
		if (argv[i] == '"')
			return (0);
		if (ft_strlen(argv) > 3 && i > 0 && ft_isdigit(argv[i - 1]) == 0
			&& argv[i + 1] == '0' && argv[i] == '0')
			return (0);
		i++;
	}
	if (ft_strlen(argv) >= 3 && argv[0] == '0' && argv[1] == '0')
		return (0);
	return (ther_is_a_number);
}

int	val_args_b(char *argv)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (argv[i] != '\0')
	{
		if (argv[i] == '\0')
			return (0);
		if ((ft_isdigit(argv[i]) == 0) && argv[i] != ' '
			&& (argv[i] != '-' && argv[i] != '+'))
			return (0);
		if ((argv[i] == '-' || argv[i] == '+')
			&& (ft_isdigit(argv[i + 1]) == 0))
			return (0);
		i++;
	}
	return (val_args2_b(argv, 0, 0));
}

int	fill_list_b(char **argv, struct s_lista **stack_a)
{
	char			**nbrs;
	int				j;
	int				i;

	j = 0;
	i = 0;
	if (val_args_b(argv[1]) == 1)
	{
		if (argv[1][i] == ' ' || argv[1][i] == '\t')
			i++;
		nbrs = ft_split(&argv[1][i], ' ');
		if (val_nbrs_b(nbrs) == 0)
			return (0);
		fill_b(stack_a, nbrs, j);
		free_nbrs_b(nbrs);
		if (val_list_b(stack_a, list_len_b(stack_a), 0) == 0)
		{
			free_circular_list_b(stack_a);
			return (0);
		}
		get_index_r_b(stack_a, NULL, 1);
	}
	else
		return (0);
	return (1);
}
