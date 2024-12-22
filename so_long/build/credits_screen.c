/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   credits_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:13:50 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/08 14:28:14 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	final_game(void *param)
{
	t_window	*window;
	int			i;

	i = -1;
	window = (t_window *)param;
	while (++i < 65)
		if (window->credits_img[i])
			mlx_delete_image(window->mlx, window->credits_img[i]);
	i = 0;
	while (window->map[i] != 0)
	{
		free(window->map[i]);
		i++;
	}
	free(window->credits_img);
	mlx_close_window(window->mlx);
}

void	load_credits_images(void *param, int i)
{
	mlx_texture_t	*texture;
	t_window		*window;
	char			*str;
	char			*n;

	window = (t_window *)param;
	window->credits_img = malloc(sizeof(mlx_image_t *) * 65);
	if (!window->credits_img)
		return ;
	while (++i <= 65)
	{
		n = ft_itoa(i);
		str = ft_strjoin("../images/credits/", n);
		free(n);
		n = str;
		str = ft_strjoin(n, ".png");
		free(n);
		texture = mlx_load_png(str);
		free(str);
		window->credits_img[i - 1] = mlx_texture_to_image(window->mlx,
				texture);
		mlx_delete_texture(texture);
	}
}

void	update_animation(void *param)
{
	t_window	*window;
	double		current_time;
	int			previous_frame;

	window = (t_window *)param;
	current_time = mlx_get_time();
	if (current_time - window->last_time >= 0.06)
	{
		window->last_time = current_time;
		previous_frame = window->current_frame;
		window->current_frame++;
		if (window->current_frame != 0 && window->credits_img[previous_frame])
			mlx_delete_image(window->mlx, window->credits_img[previous_frame]);
		if (window->credits_img[window->current_frame])
			mlx_image_to_window(window->mlx,
				window->credits_img[window->current_frame],
				abs(window->width - 1080) / 2, abs(window->heigth - 607) / 2);
		if (window->current_frame == 64)
			final_game(window);
	}
}

void	credits_screen(t_window **window)
{
	if (*window == NULL)
		return ;
	(*window)->final = 1;
	free_images(0, window);
	if ((*window)->str != NULL)
	{
		mlx_delete_image((*window)->mlx, (*window)->str);
		(*window)->str = NULL;
	}
	if ((*window)->moves_str != NULL)
	{
		mlx_delete_image((*window)->mlx, (*window)->moves_str);
		(*window)->moves_str = NULL;
	}
	(*window)->current_frame = 0;
	(*window)->last_time = mlx_get_time();
	load_credits_images(*window, 0);
	update_animation(*window);
	mlx_loop_hook((*window)->mlx, update_animation, *window);
}
