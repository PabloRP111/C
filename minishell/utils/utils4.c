/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:27:18 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/22 16:58:23 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	null_expand2(t_minis *minis, char **nl, int j, int aux)
{
	while (in_quo(minis->line, &aux, 0) == 0)
		(*nl)[j++] = minis->line[aux++];
	if ((minis->line[aux] == '\"') || (minis->line[aux] == '\''))
		aux++;
	while (minis->line[aux])
		(*nl)[j++] = minis->line[aux++];
	(*nl)[j] = '\0';
	free(minis->line);
	minis->line = (*nl);
	return (0);
}

int	null_expand2_h(t_minis *minis, char **nl, int j, int aux)
{
	while (in_quo(minis->str_aux, &aux, 0) == 0)
		(*nl)[j++] = minis->str_aux[aux++];
	if ((minis->str_aux[aux] == '\"') || (minis->str_aux[aux] == '\''))
		aux++;
	while (minis->str_aux[aux])
		(*nl)[j++] = minis->str_aux[aux++];
	(*nl)[j] = '\0';
	free(minis->str_aux);
	minis->str_aux = (*nl);
	return (0);
}

void	advance_space_2(char *str, int *i, int *j)
{
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\v'
		|| str[*i] == '\n' || str[*i] == '\r' || str[*i] == '\f')
	{
		*i += 1;
		*j += 1;
	}
}

int	its_expand(char *line, int *i)
{
	if (line[*i] == '$' && line[*i + 1] && line[*i + 1] != ' '
		&& line[*i + 1] != '\'' && line[*i + 1] != '\"')
		return (0);
	return (1);
}

int	isnt_space(t_minis *minis)
{
	char	c;
	int		i;

	i = 0;
	while (minis->line && minis->line[i])
	{
		c = minis->line[i];
		if (c != ' ')
			return (0);
		i++;
	}
	return (1);
}
