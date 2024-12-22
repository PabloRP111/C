/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 09:37:03 by prosas-p          #+#    #+#             */
/*   Updated: 2024/08/01 13:15:57 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_here_doc(t_ite *ite, int *pipefd)
{
	int		len_eof;
	int		len_line;
	char	*line;

	len_eof = ft_strlen(ite->eof);
	while (1)
	{
		line = get_next_line(0);
		len_line = ft_strlen(line);
		if (ft_strncmp(ite->eof, line, len_eof) == 0 && len_eof == len_line - 1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else
		{
			write(pipefd[1], line, len_line);
			free(line);
		}
	}
}

void	check_outfile_doc(char **argv, t_ite *ite, int *pipefd)
{
	if (its_empty_str(argv[ite->argc - 1]) == 1)
	{
		ft_printf("zsh: no such file or directory:\n");
		close3(pipefd[1], ite->fd_in, ite->fd_out);
	}
	if (access(argv[ite->argc - 1], F_OK) != -1)
	{
		if (access(argv[ite->argc - 1], W_OK) == -1)
		{
			ft_printf("zsh: permission denied: %s\n", argv[ite->argc -1]);
			close3(pipefd[1], ite->fd_in, ite->fd_out);
		}
	}
	ite->fd_out = open(argv[ite->argc - 1], O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (ite->fd_out < 0)
		dup_error2("Bad file descriptor", pipefd[1], ite->fd_out);
	if (dup2(ite->fd_out, 1) < 0)
		dup_error2("dup2", pipefd[1], ite->fd_out);
}

void	do_child_doc(int *pipefd, char **argv, t_ite *ite)
{
	char	*comand;

	comand = argv[ite->i];
	close(pipefd[0]);
	if (ite->i == 2)
	{
		check_here_doc(ite, pipefd);
		return ;
	}
	val_args_pipex(comand, ite->env, ite);
	if (ite->i == ite->argc -2)
		check_outfile_doc(argv, ite, pipefd);
	else if ((ite->i != ite->argc -2) && dup2(pipefd[1], 1) < 0)
		dup_error3("dup2", pipefd[1], ite->fd_in, ite->fd_out);
	exec_cmd(ite, ite->env);
}

void	do_pipe_doc(char **argv, t_ite *ite)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit_error("pipe");
	pid = fork();
	if (pid == -1)
		exit_error("fork");
	if (pid == 0)
		do_child_doc(pipefd, argv, ite);
	close(pipefd[1]);
	wait(NULL);
	if ((ite->i != ite->argc -2) && (dup2(pipefd[0], 0) < 0))
		dup_error2("dup2", pipefd[0], ite->fd_out);
	close(pipefd[0]);
}

void	is_here_doc(char **argv, t_ite *ite, char **env)
{
	if (ite->argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		ite->env = env;
		ite->eof = argv[2];
		while (ite->i < ite->argc -1)
		{
			do_pipe_doc(argv, ite);
			ite->i++;
		}
		close(ite->fd_out);
		exit(EXIT_SUCCESS);
	}
	return ;
}
