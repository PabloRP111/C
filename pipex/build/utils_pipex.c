/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:25:25 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/31 11:00:30 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	its_empty_str(char *str)
{
	if (str == NULL || *str == '\0')
		return (1);
	return (0);
}

void	exec_cmd(t_ite *ite, char **env)
{
	execve(ite->actual_r, ite->cmd_args, env);
	free(ite->actual_r);
	free_matrix_twice(&ite->cmd_args);
	exit_error("execve");
}
