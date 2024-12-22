/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:54:52 by prosas-p          #+#    #+#             */
/*   Updated: 2024/10/25 10:43:50 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_infile(char **argv, t_ite *ite, int *pipefd)
{
	if (access(argv[1], F_OK) != -1)
	{
		if (access(argv[1], R_OK) != -1)
		{
			ite->fd_in = open(argv[1], O_RDONLY);
			if (dup2(ite->fd_in, 0) < 0)
				dup_error3("dup2", pipefd[1], ite->fd_in, ite->fd_out);
			return ;
		}
		else
		{
			ft_printf("zsh: permission denied: %s\n", argv[1]);
			close3(pipefd[1], ite->fd_in, ite->fd_out);
		}
	}
	ft_printf("zsh: no such file or directory: %s\n", argv[1]);
	close3(pipefd[1], ite->fd_in, ite->fd_out);
	exit(EXIT_FAILURE);
}

void	check_outfile(char **argv, t_ite *ite, int *pipefd)
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
	ite->fd_out = open(argv[ite->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ite->fd_out < 0)
		dup_error3("Bad file descriptor", pipefd[1], ite->fd_in, ite->fd_out);
	if (dup2(ite->fd_out, 1) < 0)
		dup_error3("dup2", pipefd[1], ite->fd_in, ite->fd_out);
}

void	do_child(int *pipefd, char **argv, t_ite *ite, char **env)
{
	char	*comand;

	comand = argv[ite->i];
	close(pipefd[0]);
	val_args_pipex(comand, env, ite);
	if (ite->i == 2)
		check_infile(argv, ite, pipefd);
	if (ite->i == ite->argc -2)
		check_outfile(argv, ite, pipefd);
	else if ((ite->i != ite->argc -2) && dup2(pipefd[1], 1) < 0)
		dup_error3("dup2", pipefd[1], ite->fd_in, ite->fd_out);
	exec_cmd(ite, env);
}

void	do_pipe(char **argv, t_ite *ite, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		exit_error("pipe");
	pid = fork();
	if (pid == -1)
		exit_error("fork");
	if (pid == 0)
		do_child(pipefd, argv, ite, env);
	close(pipefd[1]);
	wait(NULL);
	if ((ite->i != ite->argc -2) && (dup2(pipefd[0], 0) < 0))
		dup_error2("dup2", pipefd[0], ite->fd_out);
	close(pipefd[0]);
}

int	main(int argc, char **argv, char **env)
{
	t_ite	ite;

	if (argc < 5)
		exit(0);
	ft_memset(&ite, 0, sizeof(t_ite));
	ite.i = 2;
	ite.argc = argc;
	if (argc >= 5)
	{
		while (ite.i < argc -1)
		{
			do_pipe(argv, &ite, env);
			ite.i++;
		}
		close(ite.fd_in);
		close(ite.fd_out);
	}
}
