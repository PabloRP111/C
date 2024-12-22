/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 08:13:30 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/08 09:02:33 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../LIBDEF/libdef.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_window
{
	char		**map;
	mlx_t		*mlx;
	mlx_image_t	*images[10];
	mlx_image_t	*moves_str;
	mlx_image_t	*str;
	mlx_image_t	**credits_img;
	int			current_frame;
	double		last_time;
	int			pj_x;
	int			pj_y;
	int			cmoves;
	int			ncollects4;
	int			ncollects5;
	int			ncollects4max;
	int			ncollects5max;
	int			final;
	int			width;
	int			heigth;
}	t_window;

typedef struct s_limit
{
	int	l_x;
	int	l_y;
}	t_limit;

int		val_maps(char *map, t_window **window, char *line, int i);
int		map_size(int fd);
int		check_way(char **map, int x, int y, t_limit **cur);
int		ft_is_lower(char c);
int		free_window(int n, t_window **window);
int		check_name(char **name);
int		load_images(t_window **window);
int		place_map(t_window **window, int i, int j, int type);
int		place_extras(t_window **window, int i, int j, int type);
int		free_names(int b, char ***images);
int		free_images(int b, t_window **window);
void	move_pj_down(t_window **window);
void	move_pj_up(t_window **window);
void	take_collec(t_window **window, int c_y, int c_x, int i);
void	move_pj_left(t_window **window);
void	move_pj_rigth(t_window **window);
void	get_ncollects(t_window **window);
void	credits_screen(t_window **window);
void	final_game(void *param);
void	end_game(void *param);
void	my_keyhook(mlx_key_data_t keydata, void *param);

#endif
