/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_args_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:55:57 by prosas-p          #+#    #+#             */
/*   Updated: 2024/07/31 08:57:02 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	empty_comand(char ***comand)
{
	if (its_empty_str(*comand[0]) == 1)
	{
		free_matrix_twice(comand);
		ft_printf("zsh: permission denied:\n");
		return (1);
	}
	return (0);
}

char	**find_path(char **env)
{
	char	**paths;
	char	*path;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (env[j] != NULL)
	{
		if (ft_strncmp(env[j], "PATH=", 5) == 0)
		{
			len = ft_strlen(env[j]) - 5;
			path = ft_substr(env[j], 5, len);
			paths = ft_split(path, ':');
			free(path);
			path = NULL;
			return (paths);
		}
		j++;
	}
	return (NULL);
}

int	check_comand_exits(char **paths, char *cmd, int i, t_ite *ite)
{
	char	*route;
	char	*aux;

	ite->cmd_args = ft_split(cmd, ' ');
	if (empty_comand(&ite->cmd_args) == 1)
		return (0);
	while (paths && paths[i] != NULL)
	{
		aux = ft_strjoin(paths[i], "/");
		route = ft_strjoin(aux, ite->cmd_args[0]);
		free(aux);
		if (access(route, F_OK) != -1)
		{
			ite->actual_r = route;
			return (1);
		}
		free(route);
		i++;
	}
	if (ite->cmd_args != NULL)
		ft_printf("zsh: command not found: %s\n", ite->cmd_args[0]);
	free_matrix_twice(&ite->cmd_args);
	return (0);
}

void	val_args_pipex(char *comand, char **env, t_ite *ite)
{
	char	**paths;

	paths = find_path(env);
	if (paths == NULL)
		exit(EXIT_FAILURE);
	if (check_comand_exits(paths, comand, 0, ite) == 0)
	{
		free_matrix_twice(&paths);
		exit(EXIT_FAILURE);
	}
	free_matrix_twice(&paths);
	free(paths);
}
