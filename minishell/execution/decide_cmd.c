/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decide_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:26:03 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/24 19:07:18 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builds_in(t_minis *minis, int j)
{
	if (check_redirs(minis, j) != 0)
		return (0);
	if (!minis->cmds[j].cmd || !minis->cmds[j].cmd[0])
		return (0);
	if (ft_strncmp("cd", minis->cmds[j].cmd[0], 3) == 0)
		return (bash_cd(minis, minis->cmds[j].cmd, -1, NULL), 0);
	else if (ft_strncmp("env", minis->cmds[j].cmd[0], 4) == 0)
		return (bash_env(minis), 0);
	else if (ft_strncmp("pwd", minis->cmds[j].cmd[0], 4) == 0)
		return (bash_pwd(minis), 0);
	else if (ft_strncmp("echo", minis->cmds[j].cmd[0], 5) == 0)
		return (bash_echo(minis, minis->cmds[j].cmd), 0);
	else if (ft_strncmp("exit", minis->cmds[j].cmd[0], 5) == 0)
		return (bash_exit(minis, minis->cmds[j].cmd), 0);
	else if (ft_strncmp("unset", minis->cmds[j].cmd[0], 6) == 0)
		return (bash_unset(minis, minis->cmds[j].cmd), 0);
	else if (ft_strncmp("export", minis->cmds[j].cmd[0], 7) == 0)
		return (bash_export(minis, minis->cmds[j].cmd), 0);
	return (1);
}

void	waiting(t_minis *minis)
{
	int	j;
	int	status;

	j = -1;
	while (++j < minis->n_cmd)
	{
		waitpid(minis->cmds[j].pid, &status, 0);
		minis->status = WEXITSTATUS(status);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			minis->status = 130;
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			minis->status = 131;
	}
	dup2(minis->std_in, STDIN_FILENO);
	dup2(minis->std_out, STDOUT_FILENO);
}

int	father(t_minis *minis, int j)
{
	if (minis->n_cmd > 1 && j != 0)
		close(minis->prev_pipefd[0]);
	close(minis->prev_pipefd[1]);
	minis->prev_pipefd[0] = minis->pipefd[0];
	minis->prev_pipefd[1] = minis->pipefd[1];
	return (0);
}

void	children(t_minis *minis, int j)
{
	if (j > 0)
	{
		if ((dup2(minis->prev_pipefd[0], STDIN_FILENO)) < 0)
			return ;
		close(minis->prev_pipefd[0]);
		close(minis->prev_pipefd[1]);
	}
	if (j != minis->n_cmd - 1)
	{
		if (dup2(minis->pipefd[1], STDOUT_FILENO) < 0)
			return ;
		close(minis->pipefd[0]);
		close(minis->pipefd[1]);
	}
	if (minis->cmds[j].cmd && minis->cmds[j].cmd[0])
	{
		if (builds_in(minis, j) == 0)
			exit(minis->status);
		builts_off(minis, j);
	}
	exit(minis->status);
}

int	decide_cmd(t_minis *minis, int j)
{
	minis->std_in = dup(STDIN_FILENO);
	minis->std_out = dup(STDOUT_FILENO);
	if (minis->n_cmd == 1 && ((builds_in(minis, j) == 0)))
		return (eliminar_txt_en_carpeta(minis),
			dup2(minis->std_in, STDIN_FILENO),
			dup2(minis->std_out, STDOUT_FILENO), 0);
	minis->prev_pipefd[0] = 0;
	minis->prev_pipefd[1] = -1;
	while (j < minis->n_cmd)
	{
		if (j < minis->n_cmd - 1 && pipe(minis->pipefd) == -1)
			return (set_status(minis, "creating pipe error\n", -1), 1);
		ms_setsignalson();
		minis->cmds[j].pid = fork();
		if (minis->cmds[j].pid == -1)
			return (set_status(minis, "forking error\n", -1), 1);
		if (minis->cmds[j].pid == 0)
			children(minis, j);
		else
			father(minis, j);
		j++;
	}
	waiting(minis);
	return (0);
}
