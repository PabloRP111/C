/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_collec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:28:57 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/03 13:46:38 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	get_ncollects(t_window **window)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	(*window)->ncollects4 = 0;
	(*window)->ncollects5 = 0;
	while ((*window)->map[j] != NULL)
	{
		while ((*window)->map[j][i] != 0)
		{
			if ((*window)->map[j][i] == 'c')
			{
				if (i % 2 == 0)
					(*window)->ncollects4++;
				else
					(*window)->ncollects5++;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

int	change_exit(t_window **window, int i, int j)
{
	int	pos_x;
	int	pos_y;

	pos_x = 0;
	pos_y = 0;
	while ((*window)->map[j] != NULL)
	{
		while ((*window)->map[j][i] != 0)
		{
			if ((*window)->map[j][i] == 'e')
			{
				(*window)->images[2]->instances[0].enabled = 0;
				if (mlx_image_to_window((*window)->mlx, (*window)->images[3],
						pos_x, pos_y) < 0)
					return (free_images(0, window));
			}
			i++;
			pos_x += 128;
		}
		i = 0;
		pos_x = 0;
		pos_y += 128;
		j++;
	}
	return (1);
}

void	take_collec(t_window **window, int c_y, int c_x, int i)
{
	while (i < (*window)->ncollects4max)
	{
		if ((*window)->images[4]->instances[i].x == c_x * 128
			&& (*window)->images[4]->instances[i].y == c_y * 128)
		{
			(*window)->images[4]->instances[i].enabled = 0;
			(*window)->ncollects4--;
		}
		i++;
	}
	i = 0;
	while (i < (*window)->ncollects5max)
	{
		if ((*window)->images[5]->instances[i].x == c_x * 128
			&& (*window)->images[5]->instances[i].y == c_y * 128)
		{
			(*window)->images[5]->instances[i].enabled = 0;
			(*window)->ncollects5--;
		}
		i++;
	}
	if ((*window)->ncollects4 + (*window)->ncollects5 <= 0)
		change_exit(window, 0, 0);
}
