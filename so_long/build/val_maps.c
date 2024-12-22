/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_maps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:03:35 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/03 11:30:44 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

int	check_format(char **map, int i, int j)
{
	int	line;

	line = 0;
	while (map[j] != NULL)
	{
		i = 0;
		while (map[j][i] != 0)
		{
			if (map[j][0] == '\n')
				line = 1;
			if (line == 1 && (map[j][0] != '\n' && map[j][0] != 0))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

int	check_walls(char **map, int i, int j, int m_size)
{
	int	f_len;

	if (check_format(map, 0, 0) == 0)
		return (0);
	f_len = ft_strlen(map[0]) - 2;
	while (map[j] != NULL)
	{
		i = 0;
		while (map[j][i] != 0)
		{
			if ((i == 0 || i == f_len) && map[j][i] != '1' && map[j][i] != '\n')
				return (0);
			if (map[j][i] != '1' && map[j][i] != '0' && map[j][i] != 'C'
				&& map[j][i] != 'E' && map[j][i] != 'P' && map[j][i] != '\n')
				return (0);
			i++;
		}
		if (f_len != i - 2 && j != m_size -2 && map[j][i] != 0)
			return (0);
		if (f_len != i - 1 && j == m_size -2 && map[j][i] != 0)
			return (0);
		j++;
	}
	return (1);
}

int	check_character(char **map, int i, int j)
{
	int	is_pj;
	int	is_exit;
	int	is_collectable;

	is_collectable = 0;
	is_exit = 0;
	is_pj = 0;
	while (map[j] != NULL)
	{
		i = 1;
		while (map[j][i] != 0)
		{
			if (map[j][i] == 'C')
				is_collectable++;
			else if (map[j][i] == 'E')
				is_exit++;
			else if (map[j][i] == 'P')
				is_pj++;
			i++;
		}
		j++;
	}
	if (is_collectable <= 0 || is_pj != 1 || is_exit != 1)
		return (0);
	return (1);
}

int	check_map(t_window **window, int i, int j, int m_size)
{
	t_limit	*limit;

	limit = NULL;
	if ((*window) == NULL || (*window)->map == NULL || (*window)->map[0] == 0)
		return (free_window(0, window));
	if ((check_walls((*window)->map, 0, 0, m_size) == 0)
		|| (check_character((*window)->map, 1, 1) == 0))
		return (free_window(0, window));
	while ((*window)->map[j] != NULL && (*window)->map[j][i] != 'P')
	{
		i = 0;
		while ((*window)->map[j][i] != 0 && (*window)->map[j][i] != 'P')
			i++;
		if ((*window)->map[j][i] != 'P')
			j++;
	}
	limit = (struct s_limit *)malloc(sizeof(struct s_limit));
	if (limit == NULL)
		return (free_window(0, window));
	limit->l_x = ft_strlen((*window)->map[0]) - 2;
	limit->l_y = m_size - 1;
	if (check_way((*window)->map, i, j, &limit) == 0)
		return (free_window(0, window));
	return (1);
}

int	val_maps(char *map, t_window **window, char *line, int i)
{
	char	*route;
	int		fd;
	int		fd2;
	int		m_size;

	route = ft_strjoin("../maps/", map);
	fd = open(route, O_RDONLY);
	fd2 = open(route, O_RDONLY);
	if (check_name(&route) == 0 || fd == -1 || fd2 == -1)
		return (0);
	m_size = map_size(fd2);
	*window = (struct s_window *)malloc(sizeof(t_window));
	(*window)->map = (char **)malloc(m_size * sizeof(char *));
	if (window == NULL || (*window)->map == NULL)
		return (free_window(0, window));
	while (line != NULL)
	{
		line = get_next_line(fd);
		(*window)->map[i] = line;
		i++;
	}
	if (i == 1 && line == NULL)
		return (free_window(0, window));
	return (check_map(window, 1, 1, m_size));
}
