/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 15:28:30 by prosas-p          #+#    #+#             */
/*   Updated: 2024/02/08 07:59:21 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*end_line(char **back, char **readed)
{
	char	*aux;

	if (*back != NULL)
	{
		if ((*back[0] != '\0') && (*back[0] != '\n'))
		{
			aux = ft_strdup(back);
			free_fail(readed, back);
			return (aux);
		}
	}
	free_fail(readed, NULL);
	return (NULL);
}

void	get_back(char **back, char **line, char **readed)
{
	char	*aux;
	int		i;

	i = 0;
	aux = NULL;
	free_fail(readed, NULL);
	while ((line[0][i] == back[0][i]) && (line[0][i] != '\0'))
		i++;
	if (back[0][i] != '\0')
		aux = ft_substr(*back, i, (ft_strlen(*back, 0) - i));
	free_fail(back, NULL);
	*back = aux;
}

char	*get_line_r(char **back)
{
	char	*line;
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strdup(back);
	if (aux != NULL)
	{
		line = malloc(ft_strlen(aux, 0) + 1);
		if (!line)
			return (free_fail(back, NULL));
		while ((i == 0 || (aux[i - 1] != '\n')) && (aux[i] != '\0'))
		{
			line[i] = aux[i];
			i++;
		}
		line[i] = '\0';
		free_fail(&aux, NULL);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*back;
	char		*readed;
	char		*line;
	int			bytes_reades;

	if (fd < 0)
		return (NULL);
	line = NULL;
	bytes_reades = 1;
	readed = (char *)malloc(BUFFER_SIZE + 1);
	if (readed == NULL)
		return (free_fail(&back, NULL));
	while (back == NULL || ft_strlen(back, 1) == 0)
	{
		bytes_reades = read(fd, readed, BUFFER_SIZE);
		if (bytes_reades == -1)
			return (free_fail(&back, &readed));
		readed[bytes_reades] = '\0';
		if (bytes_reades == 0)
			return (end_line(&back, &readed));
		back = ft_strjoin(&back, &readed);
	}
	line = get_line_r(&back);
	get_back(&back, &line, &readed);
	return (line);
}

// int main()
// {
//     char 	*linea;
//     int 	fd;
// 	int 	i;

// 	fd = open("leer.txt", O_RDONLY);
// 	i = 0;
// 	linea = " ";
//     while (linea != NULL)
// 	{
// 		linea = get_next_line(fd);
// 		printf("\n%d %s", i, linea);
// 		i++;
// 		free(linea);
//     }
// 	if (fd != -1)
// 		close(fd);
//     return (0);
// }
