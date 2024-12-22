/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:34:45 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/26 10:50:32 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_window	*window;

	window = (t_window *)param;
	if (mlx_is_key_down(window->mlx, MLX_KEY_ESCAPE))
		end_game(window);
	if ((*window).final != 0)
	{
		return ;
	}
	if ((keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS))
		move_pj_up(&window);
	else if ((keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS))
		move_pj_left(&window);
	else if ((keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS))
		move_pj_down(&window);
	else if ((keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS))
		move_pj_rigth(&window);
}

void	get_heigth_and_width(t_window **window, int *width, int *heigth)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*window)->map[j] != NULL && (*window)->map[j][0] != '\n')
	{
		i = 0;
		while ((*window)->map[j][i] != 0 && (*window)->map[j][i] != '\n')
		{
			if ((*window)->map[j][i] == 'p')
			{
				(*window)->pj_x = i;
				(*window)->pj_y = j;
			}
			i++;
		}
		j++;
	}
	*width = i * 128;
	*heigth = j * 128;
}

void	create_map(t_window **window)
{
	char		*moves;

	load_images(window);
	place_map(window, 0, 0, 0);
	place_extras(window, 0, 0, 1);
	get_ncollects(window);
	(*window)->ncollects4max = (*window)->ncollects4;
	(*window)->ncollects5max = (*window)->ncollects5;
	(*window)->cmoves = 0;
	(*window)->str = mlx_put_string((*window)->mlx, "MOVES: ", 15, 15);
	mlx_resize_image((*window)->str, 200, 50);
	moves = ft_itoa((*window)->cmoves);
	(*window)->moves_str = mlx_put_string((*window)->mlx, moves, 200, 15);
	mlx_resize_image((*window)->moves_str, 35, 50);
	free(moves);
	(*window)->final = 0;
}

int	main(int argc, char **argv)
{
	t_window	*window;
	int			heigth;
	int			width;

	window = NULL;
	if (argc == 1)
		return (0);
	if (argc == 2 && val_maps(argv[1], &window, "xd", 0) == 1)
	{
		get_heigth_and_width(&window, &width, &heigth);
		mlx_set_setting(MLX_STRETCH_IMAGE, true);
		window->mlx = mlx_init(width, heigth, "so_long", true);
		window->heigth = heigth;
		window->width = width;
		if (!window->mlx)
			return (0);
		create_map(&window);
		mlx_key_hook(window->mlx, &my_keyhook, window);
		mlx_loop(window->mlx);
		mlx_terminate(window->mlx);
		free(window->map);
		free(window);
	}
	else
		write(1, "Error\n", 6);
}
