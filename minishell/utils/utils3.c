/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:19:44 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/25 17:05:55 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	in_dquo(char *line, int *i, int sum)
{
	int		j;
	int		in_q;
	char	q;

	if (line == NULL || line[*i] == '\0')
		return (-1);
	q = 'q';
	change_int(&j, &in_q, -1, 1);
	while (++j <= *i)
	{
		if ((line[j] == '\"' && in_q == 1) && !(j > 0
				&& line[j - 1] == '\\' && escaped_bslash((line), j - 1) == 0))
		{
			q = line[j];
			change_int(&j, &in_q, j + 1, 0);
		}
		if ((in_q == 0 && line[j] == q) && !(j > 0 && line[j - 1] == '\\'
				&& escaped_bslash((line), j - 1) == 0))
			in_q = 1;
		*i += sum;
	}
	if (in_q == 0)
		return (0);
	return (1);
}

int	its_true_pipe(char *line, int *i)
{
	int	in_quotes;
	int	is_escaped;

	in_quotes = in_quo(line, i, 0);
	is_escaped = (*i > 0 && line[*i - 1] == '\\'
			&& escaped_bslash(line, *i - 1) == 0);
	if (line[*i] == '|' && in_quotes != 0 && !is_escaped)
		return (0);
	return (1);
}

void	print_comads(t_minis *minis)
{
	int	i;
	int	j;

	change_int(&i, &j, 0, -1);
	if (minis->line)
		printf("\nLine: %s\n", minis->line);
	while (minis->cmds && ++j < minis->n_cmd)
	{
		i = 0;
		while (minis->cmds[j].cmd && minis->cmds[j].cmd[i])
			printf("\nComand: %s\n", minis->cmds[j].cmd[i++]);
		i = 0;
		while (minis->cmds[j].redir && minis->cmds[j].redir[i])
			printf("\nRedirect: %s\n", minis->cmds[j].redir[i++]);
		printf("\nEnd of comand\n");
	}
}

void	close2(int *fd, int *fd2)
{
	if (*fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
	if (*fd2 >= 0 && *fd2 != *fd)
	{
		close(*fd2);
		*fd2 = -1;
	}
}

void	decide_start_point(t_minis *minis, int *aux)
{
	if (in_quo(minis->line, aux, 0) == 0)
	{
		while (minis->line[*aux] != '\"')
			*aux -= 1;
	}
}
