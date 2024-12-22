/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:22:28 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/24 16:05:15 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_redir(t_minis *minis, int *red, int *lp, int nc)
{
	int	i;

	i = 0;
	if ((minis->line[*lp] == '>') || (minis->line[*lp] == '<'))
	{
		if (metasim(minis->line, lp, 1, 1) == 1)
		{
			minis->cmds[nc].redir[*red][i] = minis->line[*lp];
			change_int(&i, lp, i + 1, *lp + 1);
		}
		minis->cmds[nc].redir[*red][i] = minis->line[*lp];
		change_int(&i, lp, i + 1, *lp + 1);
		advance_space(minis->line, lp);
		while (in_quo(minis->line, lp, 0) == 0 || (minis->line[*lp] != ' '
				&& metasim(minis->line, lp, 1, 3) == 3))
		{
			minis->cmds[nc].redir[*red][i] = minis->line[*lp];
			change_int(&i, lp, i + 1, *lp + 1);
		}
		minis->cmds[nc].redir[*red][i] = '\0';
		*red += 1;
	}
}

void	get_order(t_minis *minis, int *c, int *lp, int nc)
{
	int	i;

	i = 0;
	while (minis->line[*lp] && (in_quo(minis->line, lp, 0) == 0
			|| ((minis->line[*lp] != ' ')
				&& metasim(minis->line, lp, 1, 3) == 3)))
	{
		minis->cmds[nc].cmd[*c][i] = minis->line[*lp];
		change_int(&i, lp, i + 1, *lp + 1);
	}
	minis->cmds[nc].cmd[*c][i] = '\0';
	*c += 1;
}

int	get_comand(t_minis *minis, int lp, int n, int nc)
{
	int	c;
	int	red;

	change_int(&c, &red, 0, 0);
	if (alloc_mem(minis, lp, n, -1) != 0)
		return (1);
	while (minis->line[lp] && minis->line[lp] != '|'
		&& !(lp > 0 && minis->line[lp - 1] == '\\'
			&& escaped_bslash((minis->line), lp - 1) == 0))
	{
		advance_space(minis->line, &lp);
		if (metasim(minis->line, &lp, 1, 3) == 3)
			get_order(minis, &c, &lp, nc);
		advance_space(minis->line, &lp);
		if ((metasim(minis->line, &lp, 1, 0) == 0)
			|| (metasim(minis->line, &lp, 1, 1) == 1))
			get_redir(minis, &red, &lp, nc);
		advance_space(minis->line, &lp);
	}
	return (0);
}

int	get_comands(t_minis *minis, int i, int n, int lp)
{
	while (minis->line[++i])
		if (its_true_pipe(minis->line, &i) == 0)
			n++;
	minis->cmds = calloc(n + 1, sizeof(t_cmd));
	if (!minis->cmds)
		return (1);
	change_int(&minis->aux, &minis->n_cmd, 0, n);
	change_int(&i, &n, -1, 0);
	while (minis->line[++i] != '\0')
	{
		if ((metasim(minis->line, &i, 0, 1) == 1)
			|| (metasim(minis->line, &i, 0, 0) == 0))
			n++;
		else if (its_true_pipe(minis->line, &i) == 0)
		{
			if (get_comand(minis, lp, n, minis->aux) != 0)
				return (1);
			change_int(&n, &lp, 0, i + 1);
			minis->aux++;
		}
	}
	if (get_comand(minis, lp, n, minis->aux) != 0)
		return (1);
	return (0);
}

int	parsing(t_minis *minis)
{
	if (strange_character(minis, 0) != 0)
		return (1);
	if (close_quoetes(minis, 0, 'q') != 0)
		return (1);
	if (close_pipes(minis, 0) != 0)
		return (1);
	if (expand(minis, 0, -1, NULL) != 0)
		return (1);
	if (get_comands(minis, -1, 1, 0) != 0)
		return (free_minis_cmds(minis), 1);
	if (clean_unnecessary(minis, -1, -1) != 0)
		return (1);
	if (create_heredocs(minis) != 0)
		return (1);
	return (0);
}
