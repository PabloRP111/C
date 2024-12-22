/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_character.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:28:47 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/08 10:15:14 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	move_sprite(t_window **window, int n, int x, int y)
{
	char	*moves;

	(*window)->images[6]->instances[0].enabled = 0;
	(*window)->images[7]->instances[0].enabled = 0;
	(*window)->images[8]->instances[0].enabled = 0;
	(*window)->images[9]->instances[0].enabled = 0;
	(*window)->images[9]->instances[0].x += x;
	(*window)->images[9]->instances[0].y += y;
	(*window)->images[8]->instances[0].x += x;
	(*window)->images[8]->instances[0].y += y;
	(*window)->images[7]->instances[0].x += x;
	(*window)->images[7]->instances[0].y += y;
	(*window)->images[6]->instances[0].x += x;
	(*window)->images[6]->instances[0].y += y;
	(*window)->images[n]->instances[0].enabled = 1;
	(*window)->cmoves++;
	mlx_delete_image((*window)->mlx, (*window)->moves_str);
	moves = ft_itoa((*window)->cmoves);
	(*window)->moves_str = mlx_put_string((*window)->mlx, moves, 200, 15);
	mlx_resize_image((*window)->moves_str, 35, 50);
	free(moves);
}

void	move_pj_down(t_window **window)
{
	if ((*window)->map[(*window)->pj_y + 1][(*window)->pj_x] != '1'
	&& (*window)->final == 0)
	{
		if ((*window)->map[(*window)->pj_y + 1][(*window)->pj_x] == 'c')
		{
			take_collec(window, (*window)->pj_y + 1, (*window)->pj_x, 0);
			(*window)->map[(*window)->pj_y + 1][(*window)->pj_x] = 'o';
		}
		if (((*window)->map[(*window)->pj_y + 1][(*window)->pj_x] == 'e')
			&& ((*window)->ncollects4 + (*window)->ncollects5 == 0))
		{
			credits_screen(window);
			return ;
		}
		move_sprite(window, 9, 0, 128);
		(*window)->pj_y++;
	}
}

void	move_pj_up(t_window **window)
{
	if ((*window)->map[(*window)->pj_y - 1][(*window)->pj_x] != '1'
	&& (*window)->final == 0)
	{
		if ((*window)->map[(*window)->pj_y - 1][(*window)->pj_x] == 'c')
		{
			take_collec(window, (*window)->pj_y - 1, (*window)->pj_x, 0);
			(*window)->map[(*window)->pj_y - 1][(*window)->pj_x] = 'o';
		}
		if (((*window)->map[(*window)->pj_y - 1][(*window)->pj_x] == 'e')
			&& ((*window)->ncollects4 + (*window)->ncollects5 == 0))
		{
			credits_screen(window);
			return ;
		}
		move_sprite(window, 8, 0, -128);
		(*window)->pj_y--;
	}
}

void	move_pj_rigth(t_window **window)
{
	if ((*window)->map[(*window)->pj_y][(*window)->pj_x + 1] != '1'
	&& (*window)->final == 0)
	{
		if ((*window)->map[(*window)->pj_y][(*window)->pj_x + 1] == 'c')
		{
			take_collec(window, (*window)->pj_y, (*window)->pj_x + 1, 0);
			(*window)->map[(*window)->pj_y][(*window)->pj_x + 1] = 'o';
		}
		if (((*window)->map[(*window)->pj_y][(*window)->pj_x + 1] == 'e')
			&& ((*window)->ncollects4 + (*window)->ncollects5 == 0))
		{
			credits_screen(window);
			return ;
		}
		move_sprite(window, 7, 128, 0);
		(*window)->pj_x++;
	}
}

void	move_pj_left(t_window **window)
{
	if ((*window)->map[(*window)->pj_y][(*window)->pj_x - 1] != '1'
	&& (*window)->final == 0)
	{
		if ((*window)->map[(*window)->pj_y][(*window)->pj_x - 1] == 'c')
		{
			take_collec(window, (*window)->pj_y, (*window)->pj_x - 1, 0);
			(*window)->map[(*window)->pj_y][(*window)->pj_x - 1] = 'o';
		}
		if (((*window)->map[(*window)->pj_y][(*window)->pj_x - 1] == 'e')
			&& ((*window)->ncollects4 + (*window)->ncollects5 == 0))
		{
			credits_screen(window);
			return ;
		}
		move_sprite(window, 6, -128, 0);
		(*window)->pj_x--;
	}
}
