/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra_pipex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 09:51:11 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/31 08:45:51 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_matrix_twice(char ***matrix)
{
	int	j;

	j = 0;
	while (matrix != NULL && (*matrix) != NULL && (*matrix)[j] != NULL)
	{
		free((*matrix)[j]);
		(*matrix)[j] = NULL;
		j++;
	}
	free((*matrix));
	(*matrix) = NULL;
}

void	null_matrix(char ***matrix)
{
	int	j;

	j = 0;
	while ((*matrix[j]) != NULL)
	{
		(*matrix[j]) = NULL;
		j++;
	}
	*matrix = NULL;
	matrix = NULL;
}

void	free_matrix(char ***matrix)
{
	int	j;

	j = 0;
	while (matrix != NULL && (*matrix) != NULL && (*matrix)[j] != NULL)
	{
		free((*matrix)[j]);
		(*matrix)[j] = NULL;
		j++;
	}
	(*matrix) = NULL;
}

void	final_free(char ***matrix, char **str, char **str2)
{
	if (matrix && *matrix)
		free_matrix_twice(matrix);
	if (str && *str)
	{
		free(*str);
		*str = NULL;
		str = NULL;
	}
	if (str2 && *str2)
	{
		free(*str2);
		*str2 = NULL;
		str2 = NULL;
	}
}

void	free2(char ***matrix, char **str)
{
	if (matrix && *matrix)
		free_matrix_twice(matrix);
	if (str && *str)
	{
		free(*str);
		*str = NULL;
		str = NULL;
	}
}
