/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 07:52:06 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/08 10:36:39 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

void	end_game(void *param)
{
	t_window	*window;
	int			i;

	i = 0;
	window = (t_window *)param;
	while (window->map[i] != 0)
	{
		free(window->map[i]);
		i++;
	}
	mlx_close_window(window->mlx);
	free_images(0, &window);
}

int	free_window(int n, t_window **window)
{
	int	j;

	j = 0;
	if ((*window) != NULL)
	{
		if ((*window)->map != NULL)
		{
			while ((*window)->map[j] != NULL)
			{
				free((*window)->map[j]);
				(*window)->map[j] = NULL;
				j++;
			}
			free((*window)->map);
			(*window)->map = NULL;
		}
		free((*window));
		window = NULL;
	}
	return (n);
}

int	free_images(int b, t_window **window)
{
	int	i;

	i = 0;
	if (window == NULL || *window == NULL)
		return (b);
	while ((*window)->images[i] != NULL)
	{
		mlx_delete_image((*window)->mlx, (*window)->images[i]);
		(*window)->images[i] = NULL;
		i++;
	}
	return (b);
}

int	free_names(int b, char ***images)
{
	int	j;

	j = 0;
	if (images && *images)
	{
		free(*images);
		*images = NULL;
	}
	images = NULL;
	return (b);
}
