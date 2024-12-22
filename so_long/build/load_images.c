/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:19:55 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/03 12:07:48 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

int	type_image(char c)
{
	if (c == 'o' || c == 'p' || c == 'c')
		return (0);
	else if (c == '1' || c == 'e')
		return (1);
	return (1);
}

int	place_map(t_window **window, int i, int j, int type)
{
	int	pos_x;
	int	pos_y;

	pos_x = 0;
	pos_y = 0;
	while ((*window)->map[j] != NULL)
	{
		while ((*window)->map[j][i] != 0)
		{
			if ((*window)->map[j][i] != '\n')
			{
				type = type_image((*window)->map[j][i]);
				if (mlx_image_to_window((*window)->mlx, (*window)->images[type],
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

void	get_img_names(char ***imgs)
{
	(*imgs) = malloc(10 * sizeof(char *));
	(*imgs)[0] = "../images/floor.png";
	(*imgs)[1] = "../images/wall.png";
	(*imgs)[2] = "../images/Exit1.png";
	(*imgs)[3] = "../images/Exit2.png";
	(*imgs)[4] = "../images/CollectionItem.png";
	(*imgs)[5] = "../images/CollectionItem2.png";
	(*imgs)[6] = "../images/left.png";
	(*imgs)[7] = "../images/rigth.png";
	(*imgs)[8] = "../images/up.png";
	(*imgs)[9] = "../images/down.png";
}

int	load_images(t_window **window)
{
	mlx_texture_t	*texture;
	char			**imgs;
	int				count;

	count = -1;
	get_img_names(&imgs);
	while (++count < 10)
	{
		texture = mlx_load_png(imgs[count]);
		if (!texture)
			return (free_names(0, &imgs));
		(*window)->images[count] = mlx_texture_to_image((*window)->mlx,
				texture);
		if (!(*window)->images[count])
			return (free_names(0, &imgs));
		mlx_delete_texture(texture);
	}
	return (free_names(1, &imgs));
}
