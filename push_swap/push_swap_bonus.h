/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:45:55 by prosas-p          #+#    #+#             */
/*   Updated: 2024/06/07 11:11:32 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H
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

struct s_moves
{
	struct s_moves	*next;
	struct s_moves	*prev;
	char			*move;
}	;

int		fill_list_mult_b(char **argv, struct s_lista **stack_a);
int		fill_list_b(char **argv, struct s_lista **stack_a);
void	free_circular_list_b(struct s_lista **stack);
int		list_len_b(struct s_lista **stack);
int		free_b(char **line);
int		val_list_b(struct s_lista **stack_a, int len, int index);
void	free_circular_list_b(struct s_lista **stack);
int		val_nbrs_b(char **nbrs);
long	ft_atoi_swap_b(const char *str);
int		is_ordered(struct s_lista **stack_a, struct s_lista **stack_b);
int		make_mb(struct s_lista **stack_a, struct s_lista **stack_b,
			char *move);
void	swap_b(struct s_lista **stack);
void	push_b(struct s_lista **stack_one, struct s_lista **stack_two);
void	rotate_b(struct s_lista **stack);
void	reverse_b(struct s_lista **stack);
void	con_front_list_b(struct s_lista **node, struct s_lista **stack);
void	dis_node_list_b(struct s_lista **node, struct s_lista **stack);
void	fill_b(struct s_lista **stack_a, char **argv, int j);
void	get_index_r_b(struct s_lista **current, struct s_lista **old_min_node,
			int index);

#endif
