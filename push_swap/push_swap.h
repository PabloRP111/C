/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:45:55 by prosas-p          #+#    #+#             */
/*   Updated: 2024/06/03 11:40:44 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "LibDEF/libdef.h"

struct s_lista
{
	struct s_lista	*next;
	struct s_lista	*prev;
	int				n;
	int				index;
	int				seq;
	int				exit_cos;
	int				enter_cos;
	int				total_cos;
}	;

int		fill_list(char **argv, struct s_lista **stack_a);
int		fill_list_mult_args(char **argv, struct s_lista **stack_a);
int		list_len(struct s_lista **stack_a);
int		val_nbrs(char **nbrs);
int		is_ordered_five(struct s_lista **stack_a, int min, int len);
int		is_ordered(struct s_lista **stack_a, struct s_lista **stack_b, int len);
int		val_list(struct s_lista **stack_a, int len, int index);
void	free_circular_list(struct s_lista **stack);
void	get_index_r(struct s_lista **stack_a,
			struct s_lista **old_min_node, int index);
void	print_list(struct s_lista **stack_a);
void	con_front_list(struct s_lista **node, struct s_lista **stack);
void	dis_node_list(struct s_lista **node, struct s_lista **stack);
void	fill(struct s_lista **stack_a, char **argv, int j);
long	ft_atoi_swap(const char *str);
void	push(struct s_lista **stack_a, struct s_lista **stack_b);
void	swap(struct s_lista **stack_a);
void	rotate(struct s_lista **stack_a);
void	reverse(struct s_lista **stack_a);
void	order(struct s_lista **stack_a, struct s_lista **stack_b);
void	makem_sl(struct s_lista **stack_a, struct s_lista **stack_b,
			char *move);
void	choose_move(struct s_lista **stack_a, struct s_lista **stack_b);
void	calc_costs(struct s_lista **stack_a, struct s_lista **stack_b,
			int len_b, int distance);
int		check_push(struct s_lista **stack_a, struct s_lista **stack_b,
			struct s_lista **temp);
void	manage_rotate(struct s_lista **stack_a, struct s_lista **stack_b,
			int *n_rotate_b, int *n_rotate_a);
void	get_sequences(struct s_lista **stack);
void	short_five(struct s_lista **stack_a, struct s_lista **stack_b,
			int len);
void	get_max_and_min(struct s_lista **stack_a, int *max_n, int *min_n);

#endif
