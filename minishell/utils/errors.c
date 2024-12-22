/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:42:26 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/22 15:15:56 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_status(t_minis *minis, char *error, int status)
{
	int	i;

	i = -1;
	while (error && error[++i])
		write(2, &error[i], 1);
	minis->status = status;
}

void	free_exit(t_minis *minis)
{
	if (minis->cmds)
		free_minis_cmds(minis);
	if (minis->line)
		free(minis->line);
	free_matrix_twice(minis->p_env);
	free(minis->path_here_doc);
}

void	free_matrix_twice(char **matrix)
{
	int	j;

	j = 0;
	while (matrix != NULL && matrix[j] != NULL)
	{
		free(matrix[j]);
		matrix[j] = NULL;
		j++;
	}
	if (matrix)
		free(matrix);
	matrix = NULL;
}

void	free_minis_cmds(t_minis *minis)
{
	int	z;

	z = -1;
	minis->std_in = 0;
	minis->std_out = 0;
	while (++z < minis->n_cmd)
	{
		free_matrix_twice(minis->cmds[z].cmd);
		free_matrix_twice(minis->cmds[z].redir);
	}
	if (minis->cmds)
		free(minis->cmds);
	minis->cmds = NULL;
	g_sig = 0;
}
