/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 11:01:15 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/24 14:46:00 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	eliminar_txt_en_carpeta(t_minis *minis)
{
	char			*n;
	char			*name;
	char			*tempdir;
	char			*path;

	tempdir = ft_strjoin(minis->path_here_doc, "/temps/");
	while (minis->heredocs_c > 0)
	{
		n = ft_itoa(minis->heredocs_c);
		name = ft_strjoin("heredoc_", n);
		if (!name)
			return (1);
		path = ft_strjoin(tempdir, name);
		unlink(path);
		free2(&name, &n);
		free(path);
		minis->heredocs_c--;
	}
	free(tempdir);
	return (0);
}

int	close_heredoc(t_minis *minis, char *name, int fd, int i)
{
	char	*line;

	while (1)
	{
		i++;
		ms_setsignalhere();
		line = readline("> ");
		reopen_fd();
		if (line && ft_strncmp(line, name, (ft_strlen(name) + 1)) != 0)
		{
			if (expand_heredoc(minis, line, NULL, -1) == 0)
				line = minis->str_aux;
			write (fd, line, ft_strlen(line));
			write (fd, "\n", 1);
			free(line);
		}
		else
			break ;
	}
	if (!line && g_sig == 0)
		signal_cd_heredoc(name, i);
	free(line);
	return (0);
}

int	open_heredoc(t_minis *minis, int j, int z, int i)
{
	int		fd;
	char	*name;
	char	*path;
	char	*n;

	if (g_sig != 0)
		return (change_int(&minis->status, NULL, 128 + g_sig, 0), 1);
	minis->heredocs_c += 1;
	n = ft_itoa(minis->heredocs_c);
	name = ft_strjoin("/temps/heredoc_", n);
	path = ft_strjoin(minis->path_here_doc, name);
	if (!name || !path)
		return (1);
	free2(&name, &n);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	name = ft_substr(minis->cmds[z].redir[j], 2,
			(ft_strlen(minis->cmds[z].redir[j]) - 2));
	if (close_heredoc(minis, name, fd, 0) != 0)
		return (free(minis->cmds[i].redir[j]), free2(&name, &path), 1);
	free(minis->cmds[i].redir[j]);
	minis->cmds[i].redir[j] = ft_strjoin("<", path);
	close(fd);
	free2(&name, &path);
	return (0);
}

int	create_heredocs(t_minis *minis)
{
	int	i;
	int	j;
	int	z;

	change_int(&i, &z, -1, -1);
	while (++i < minis->n_cmd)
	{
		z++;
		j = 0;
		while (minis->cmds[i].redir && minis->cmds[i].redir[j])
		{
			if (minis->cmds[i].redir[j][0] == '<'
				&& minis->cmds[i].redir[j][1] == '<')
				if (open_heredoc(minis, j, z, i) != 0)
					return (1);
			j++;
		}
	}
	return (0);
}
