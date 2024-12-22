/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:55:16 by prosas-p          #+#    #+#             */
/*   Updated: 2024/06/07 11:11:11 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

int	val_move(char *m)
{
	int	valid;

	valid = 0;
	if (ft_strlen(m) == 3)
	{
		if (ft_strncmp(m, "pa", 2) == 0 || ft_strncmp(m, "pb", 2) == 0)
			valid = 1;
		else if (ft_strncmp(m, "sa", 2) == 0 || ft_strncmp(m, "sb", 2) == 0)
			valid = 1;
		else if (ft_strncmp(m, "ra", 2) == 0 || ft_strncmp(m, "rb", 2) == 0)
			valid = 1;
		else if (ft_strncmp(m, "rr", 2) == 0)
			valid = 1;
		else if (ft_strncmp(m, "ss", 2) == 0 || ft_strncmp(m, "rb", 2) == 0)
			valid = 1;
	}
	else if (ft_strlen(m) == 4)
	{
		if (ft_strncmp(m, "rra", 3) == 0 || ft_strncmp(m, "rrb", 3) == 0)
			valid = 1;
		else if (ft_strncmp(m, "rrr", 3) == 0)
			valid = 1;
	}
	return (valid);
}

void	print_result(struct s_lista **stack_a, struct s_lista **stack_b,
		struct s_moves **move, struct s_moves *new_move)
{
	while ((*move)->prev != NULL)
		(*move) = (*move)->prev;
	while ((*move) != NULL && (*move)->move != 0)
	{
		if (make_mb(stack_a, stack_b, (*move)->move) == 1)
		{
			new_move = (*move);
			(*move) = (*move)->next;
			free(new_move->move);
			free(new_move);
		}
		else
		{
			write(1, "KO\n", 3);
			return ;
		}
	}
	if (is_ordered(stack_a, stack_b) == 1)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	if ((*move))
		free((*move));
}

int	check_line_b(struct s_moves **move, struct s_moves **new_move,
		char **line)
{
	if (*line != 0 && val_move(*line) == 1)
	{
		(*new_move) = (struct s_moves *)ft_calloc(1, sizeof(struct s_moves));
		if (!(*new_move))
			return (free_b(line));
		(*move)->move = *line;
		(*move)->next = (*new_move);
		(*new_move)->prev = (*move);
		(*move) = (*new_move);
	}
	else if (*line != 0)
	{
		while (*move != NULL)
		{
			(*new_move) = *move;
			*move = (*move)->prev;
			free((*new_move)->move);
			free((new_move));
		}
		free(*line);
		return (write(2, "Error\n", 6));
	}
	return (1);
}

int	get_moves(struct s_moves **move, char	*line)
{
	struct s_moves	*new_move;

	new_move = NULL;
	(*move) = (struct s_moves *)ft_calloc(1, sizeof(struct s_moves));
	if (!(*move))
		return (0);
	(*move)->move = NULL;
	(*move)->prev = NULL;
	while (line != 0)
	{
		line = get_next_line(0);
		if (check_line_b(move, &new_move, &line) != 1)
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	struct s_lista	*stack_a;
	struct s_lista	*stack_b;
	struct s_moves	*move;
	int				berror;

	berror = 0;
	stack_a = NULL;
	stack_b = NULL;
	if (argc == 2)
		berror = fill_list_b(argv, &stack_a);
	else if (argc > 2)
		berror = fill_list_mult_b(argv, &stack_a);
	else if (argc == 1)
		return (0);
	if (berror == 0)
		write(2, "Error\n", 6);
	else
	{
		if (get_moves(&move, "xd") == 1)
			print_result(&stack_a, &stack_b, &move, NULL);
		free_circular_list_b(&stack_a);
		free_circular_list_b(&stack_b);
	}
	exit(EXIT_SUCCESS);
}
