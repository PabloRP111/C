/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_way.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:03:35 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/03 11:31:51 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

int	free_limit(int n, t_limit **cur)
{
	(*cur)->l_x = 0;
	(*cur)->l_y = 0;
	free(*cur);
	cur = NULL;
	return (n);
}

void	flood_fill_sl(char **map, int x, int y, t_limit *cur)
{
	if (x <= 0 || x >= cur->l_x || y <= 0 || y >= cur->l_y || map[y][x] == '1'
		|| ft_is_lower(map[y][x]) == 1 || map[y][x] == 'o')
		return ;
	map[y][x] = ft_tolower(map[y][x]);
	if (map[y][x] == '0')
		map[y][x] = 'o';
	flood_fill_sl(map, x + 1, y, cur);
	flood_fill_sl(map, x - 1, y, cur);
	flood_fill_sl(map, x, y + 1, cur);
	flood_fill_sl(map, x, y - 1, cur);
}

int	check_way(char **map, int x, int y, t_limit **cur)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	flood_fill_sl(map, x, y, *cur);
	while (map[j] != NULL)
	{
		i = 0;
		while (map[j][i] != 0)
		{
			if (map[j][i] == 'E' || map[j][i] == 'C' || map[j][i] == 'P')
				return (free_limit(0, cur));
			i++;
		}
		j++;
	}
	return (free_limit(1, cur));
}
