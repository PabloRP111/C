/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:28:57 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/03 12:10:41 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	display_character(t_window **window, int pos_x, int pos_y, int *type)
{
	if (mlx_image_to_window((*window)->mlx, (*window)->images[6],
			pos_x, pos_y) < 0)
		*type = free_images(0, window);
	if (mlx_image_to_window((*window)->mlx, (*window)->images[7],
			pos_x, pos_y) < 0)
		*type = free_images(0, window);
	if (mlx_image_to_window((*window)->mlx, (*window)->images[8],
			pos_x, pos_y) < 0)
		*type = free_images(0, window);
	if (mlx_image_to_window((*window)->mlx, (*window)->images[9],
			pos_x, pos_y) < 0)
		*type = free_images(0, window);
	(*window)->images[6]->instances[0].enabled = 0;
	(*window)->images[7]->instances[0].enabled = 0;
	(*window)->images[8]->instances[0].enabled = 0;
	(*window)->images[9]->instances[0].enabled = 1;
}

void	display_collectable(t_window **window, int pos_x, int pos_y, int *type)
{
	if ((pos_x / 128) % 2 == 0)
	{
		if (mlx_image_to_window((*window)->mlx, (*window)->images[4],
				pos_x, pos_y) < 0)
			*type = free_images(0, window);
	}
	else
	{
		if (mlx_image_to_window((*window)->mlx, (*window)->images[5],
				pos_x, pos_y) < 0)
			*type = free_images(0, window);
	}
}

void	display_exit(t_window **window, int pos_x, int pos_y, int *type)
{
	if (mlx_image_to_window((*window)->mlx, (*window)->images[2],
			pos_x, pos_y) < 0)
		*type = free_images(0, window);
}

int	place_extras(t_window **window, int i, int j, int type)
{
	int	pos_x;
	int	pos_y;

	pos_x = 0;
	pos_y = 0;
	while ((*window)->map[j] != NULL && type == 1)
	{
		while ((*window)->map[j][i] != 0 && type == 1)
		{
			if ((*window)->map[j][i] == 'p')
				display_character(window, pos_x, pos_y, &type);
			else if ((*window)->map[j][i] == 'c')
				display_collectable(window, pos_x, pos_y, &type);
			else if ((*window)->map[j][i] == 'e')
				display_exit(window, pos_x, pos_y, &type);
			i++;
			pos_x += 128;
		}
		i = 0;
		pos_x = 0;
		pos_y += 128;
		j++;
	}
	return (type);
}
