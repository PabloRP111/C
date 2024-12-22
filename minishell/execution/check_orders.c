/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_orders.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:29:48 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/25 17:23:55 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	empty_comand(char *comand)
{
	if (empty_str(comand) == -1)
		return (0);
	if (empty_str(comand) == 0)
	{
		write(2, "Command '' not found:\n", 23);
		return (0);
	}
	return (1);
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

void	check_absolute_path(t_minis *minis, int j)
{
	struct stat	pathstat;

	if (stat(minis->cmds[j].cmd[0], &pathstat) == -1)
		return (printf("\n%s", minis->cmds[j].cmd[0]),
			set_status(minis, " No such file or directory\n", 127));
	else if (S_ISDIR(pathstat.st_mode))
		return (printf("\n%s", minis->cmds[j].cmd[0]),
			set_status(minis, " Is directory\n", 126));
	else if (S_ISREG(pathstat.st_mode) & !(pathstat.st_mode & S_IXUSR))
		return (printf("\n%s", minis->cmds[j].cmd[0]),
			set_status(minis, " Permission denied\n", 126));
	else if (S_ISREG(pathstat.st_mode) && (pathstat.st_mode & S_IXUSR))
		if (execve(minis->cmds[j].cmd[0], minis->cmds[j].cmd,
				minis->p_env) == -1)
			return (set_status(minis, " Execution failed\n", 126));
}

int	check_comand_exits(t_minis *minis, int i, int j)
{
	char	*route;
	char	*aux;

	if (!minis->line || !minis->cmds)
		return (1);
	if (empty_comand(minis->cmds[j].cmd[0]) == 0)
		return (1);
	while (minis->paths && minis->paths[i] != NULL)
	{
		aux = ft_strjoin(minis->paths[i], "/");
		route = ft_strjoin(aux, minis->cmds[j].cmd[0]);
		free(aux);
		if (access(route, F_OK) != -1)
		{
			minis->cmd_route = route;
			return (0);
		}
		free(route);
		i++;
	}
	if (minis->cmds[j].cmd[0] != NULL)
		return (write(2, "Command ", 8),
			write(2, minis->cmds[j].cmd[0], ft_strlen(minis->cmds[j].cmd[0])),
			write(2, " not found\n", 11), set_status(minis, NULL, 127), 1);
	return (1);
}

void	builts_off(t_minis *minis, int j)
{
	minis->paths = find_path(minis->p_env);
	if (ft_strchr(minis->cmds[j].cmd[0], '/') != NULL)
		check_absolute_path(minis, j);
	else if (check_comand_exits(minis, 0, j) == 1)
	{
		exit(minis->status);
	}
	if (check_redirs(minis, j) != 0)
		return ;
	execve(minis->cmd_route, minis->cmds[j].cmd, minis->p_env);
}
