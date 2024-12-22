/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:50:49 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/25 17:09:17 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	append_redirs(t_minis *minis, int j, int i)
{
	int		fd;
	char	*name;

	name = minis->cmds[j].redir[i];
	fd = open((name + 2), O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (set_status(minis, "Permission denied", 1), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (set_status(minis, "Error in redirections", 1), 1);
	close(fd);
	return (0);
}

int	exit_redirs(t_minis *minis, int j, int i)
{
	int		fd;
	char	*name;

	name = minis->cmds[j].redir[i];
	fd = open((name + 1), O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (set_status(minis, "Permission denied", 1), 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (set_status(minis, "Error in redirections", 1), 1);
	close(fd);
	return (0);
}

int	enter_redirs(t_minis *minis, int j, int i)
{
	int		fd;
	char	*name;

	name = minis->cmds[j].redir[i];
	fd = open((name + 1), O_RDONLY);
	if (fd == -1)
		return (set_status(minis, "Not such file or directory", 1), 1);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (set_status(minis, "Error in redirections", 14), 1);
	close(fd);
	return (0);
}

int	check_redirs(t_minis *minis, int j)
{
	int	i;

	i = -1;
	if (!minis->cmds || !minis->cmds[j].redir || !minis->cmds[j].redir[0])
		return (0);
	while (minis->cmds[j].redir[++i])
	{
		if (minis->cmds[j].redir[i][0] == '<')
		{
			if (enter_redirs(minis, j, i) != 0)
				return (1);
		}
		else if (minis->cmds[j].redir[i][0] == '>')
		{
			if (minis->cmds[j].redir[i][1] == '>')
			{
				if (append_redirs(minis, j, i) != 0)
					return (1);
			}
			else if (exit_redirs(minis, j, i) != 0)
				return (1);
		}
	}
	return (0);
}
