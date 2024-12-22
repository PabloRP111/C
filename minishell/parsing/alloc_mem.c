/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 08:21:54 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/22 14:57:50 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_len(t_minis *minis, int *len, int j)
{
	while (minis->line[j] && its_true_pipe(minis->line, &j) != 0)
	{
		advance_space_2(minis->line, &j, len);
		if ((metasim(minis->line, &j, 0, 0) == 0)
			|| (metasim(minis->line, &j, 0, 1) == 1))
		{
			advance_space(minis->line, &j);
			while (minis->line[j] && minis->line[j] != ' '
				&& (metasim(minis->line, &j, 0, 3) == 3))
				;
			advance_space(minis->line, &j);
		}
		if (minis->line[j])
		{
			*len += 1;
			j++;
		}
	}
}

int	alloc_mem3(t_minis *minis, int c, int i, int n)
{
	int	len;

	if (n > 0)
		minis->cmds[minis->aux].redir = ft_calloc(n + 1, sizeof(char *));
	if (n > 0 && !minis->cmds[minis->aux].redir)
		return (1);
	if (c > 0)
		minis->cmds[minis->aux].cmd = (char **)ft_calloc(c + 1, sizeof(char *));
	if (c > 0 && !minis->cmds[minis->aux].cmd)
		return (1);
	len = 0;
	cmd_len(minis, &len, 0);
	while (++i < c)
	{
		minis->cmds[minis->aux].cmd[i] = ft_calloc(len + 1, sizeof(char));
		if (!minis->cmds[minis->aux].cmd[i])
			return (1);
	}
	if (c > 0)
		minis->cmds[minis->aux].cmd[i] = NULL;
	if (c == 0)
		minis->cmds[minis->aux].cmd = NULL;
	return (0);
}

int	alloc_mem2(t_minis *minis, int n, int lp, int c)
{
	while (minis->line[lp] && minis->line[lp] != '|')
	{
		advance_space(minis->line, &lp);
		if ((in_quo(minis->line, &lp, 0) == 0 || (minis->line[lp] != ' '))
			&& metasim(minis->line, &lp, 1, 3) == 3)
			c++;
		while (in_quo(minis->line, &lp, 0) == 1 && (minis->line[lp] != ' ')
			&& metasim(minis->line, &lp, 0, 3) == 3)
			;
		while (in_quo(minis->line, &lp, 0) == 0 || (minis->line[lp] == '"'))
			lp++;
		if (in_quo(minis->line, &lp, 0) == 1
			&& (metasim(minis->line, &lp, 0, 1) == 1
				|| metasim(minis->line, &lp, 0, 0) == 0))
		{
			advance_space(minis->line, &lp);
			while (in_quo(minis->line, &lp, 0) == 0 || (minis->line[lp] != ' '
					&& metasim(minis->line, &lp, 1, 3) == 3))
				lp++;
		}
	}
	return (alloc_mem3(minis, c, -1, n));
}

int	alloc_mem(t_minis *minis, int lp, int n, int aux)
{
	if (alloc_mem2(minis, n, lp, 0) != 0)
		return (1);
	while (++aux < n)
	{
		while (metasim(minis->line, &lp, 0, 3) == 3)
			;
		if ((metasim(minis->line, &lp, 1, 1) == 1)
			|| (metasim(minis->line, &lp, 1, 0) == 0))
		{
			if (metasim(minis->line, &lp, 0, 1) == 1)
				minis->ite += 2;
			if (metasim(minis->line, &lp, 0, 0) == 0)
				minis->ite += 1;
			advance_space(minis->line, &lp);
			while ((in_quo(minis->line, &lp, 0) == 0
					|| (minis->line[lp] != ' '))
				&& metasim(minis->line, &lp, 0, 3) == 3)
				minis->ite++;
			minis->cmds[minis->aux].redir[aux]
				= ft_calloc(minis->ite + 1, sizeof(char));
			if (!minis->cmds[minis->aux].redir[aux])
				return (1);
		}
	}
	return (0);
}
