/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:41:22 by prosas-p          #+#    #+#             */
/*   Updated: 2024/06/27 17:34:36 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

int	map_size(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	if (line != NULL)
	{
		i++;
		free(line);
	}
	while (line != NULL)
	{
		line = get_next_line(fd);
		i++;
		free(line);
	}
	return (i);
}

int	ft_is_lower(char c)
{
	if (c >= 97 && c <= 122)
		return (1);
	return (0);
}

int	check_name(char **name)
{
	char	*substring;
	int		i;

	i = ft_strlen(*name);
	if (i < 6)
		return (0);
	substring = ft_substr(*name, i - 4, 4);
	if (substring == 0)
	{
		free(*name);
		return (0);
	}
	if (ft_strncmp(substring, ".ber", 4) != 0)
	{
		free(substring);
		free(*name);
		return (0);
	}
	free(substring);
	free(*name);
	return (1);
}
