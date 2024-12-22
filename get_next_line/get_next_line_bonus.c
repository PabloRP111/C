/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 12:10:08 by prosas-p          #+#    #+#             */
/*   Updated: 2024/02/07 20:35:16 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*end_line_bonus(char **back, char **readed)
{
	char	*aux;

	if (*back != NULL)
	{
		if ((*back[0] != '\0') && (*back[0] != '\n'))
		{
			aux = ft_strdup_bonus(back);
			free_fail_bonus(readed, back);
			return (aux);
		}
	}
	free_fail_bonus(readed, NULL);
	return (NULL);
}

void	get_back_bonus(char **back, char **line, char **readed)
{
	char	*aux;
	int		i;

	i = 0;
	aux = NULL;
	free_fail_bonus(readed, NULL);
	while ((line[0][i] == back[0][i]) && (line[0][i] != '\0'))
		i++;
	if (back[0][i] != '\0')
		aux = ft_substr_bonus(*back, i, (ft_strlen_bonus(*back, 0) - i));
	free_fail_bonus(back, NULL);
	*back = aux;
}

char	*get_line_bonus(char **back)
{
	char	*line;
	char	*aux;
	int		i;

	i = 0;
	aux = ft_strdup_bonus(back);
	if (aux != NULL)
	{
		line = malloc(ft_strlen_bonus(aux, 0) + 1);
		if (!line)
			return (free_fail_bonus(back, NULL));
		while ((i == 0 || (aux[i - 1] != '\n')) && (aux[i] != '\0'))
		{
			line[i] = aux[i];
			i++;
		}
		line[i] = '\0';
		free_fail_bonus(&aux, NULL);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*back[4096];
	char		*readed;
	char		*line;
	int			bytes_reades;

	if (fd < 0)
		return (NULL);
	line = NULL;
	bytes_reades = 1;
	readed = (char *)malloc(BUFFER_SIZE + 1);
	if (readed == NULL)
		return (free_fail_bonus(&back[fd], NULL));
	while (back[fd] == NULL || ft_strlen_bonus(back[fd], 1) == 0)
	{
		bytes_reades = read(fd, readed, BUFFER_SIZE);
		if (bytes_reades == -1)
			return (free_fail_bonus(&back[fd], &readed));
		readed[bytes_reades] = '\0';
		if (bytes_reades == 0)
			return (end_line_bonus(&back[fd], &readed));
		back[fd] = ft_strjoin_bonus(&back[fd], &readed);
	}
	line = get_line_bonus(&back[fd]);
	get_back_bonus(&back[fd], &line, &readed);
	return (line);
}

// int main()
// {
//     int fd;
// 	int fd2;
// 	int fd3;
//     char *linea;
// 	fd = open("leer.txt", O_RDONLY);
// 	fd2 = open("leer.txt", O_RDONLY);
// 	fd3 = open("leer.txt", O_RDONLY);
// 	linea = get_next_line(fd);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd2);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd3);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd2);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd3);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd2);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd3);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd3);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd2);
// 	printf("\n%s", linea);
// 	linea = get_next_line(fd3);
// 	printf("\n%s", linea);
// 	// linea = " ";
// while (linea != NULL)
// {
// 	linea = get_next_line(fd);
// 	printf("%d%s", i, linea);
// 	i++;
// }
// 	if (fd != -1)
// 		close(fd);
// 	if (fd2 != -1)
// 		close(fd);
// 	if (fd3 != -1)
// 		close(fd);
//     return (0);
// }
