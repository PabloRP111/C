/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:10:36 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/15 15:43:28 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dif_str(char c)
{
	if (c == ' ' || c == '$' || c == '\"' || c == '\'' || c == '>'
		|| c == '<')
		return (0);
	if (ft_isalnum(c) == 0)
		return (0);
	return (1);
}

void	change_int(int *i1, int *i2, int v1, int v2)
{
	if (i1)
		*i1 = v1;
	if (i2)
		*i2 = v2;
}

int	advance_q(char *line, int *i)
{
	char	q;

	if (line == NULL || line[*i] == '\0')
		return (-1);
	if (line[*i] == '\"' || line[*i] == '\'')
	{
		q = line[*i];
		*i += 1;
		while (line[*i] && line[*i] != q)
			*i += 1;
		return (0);
	}
	return (1);
}

int	in_quo(char *line, int *i, int sum)
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
		if (((line[j] == '\"' || line[j] == '\'') && in_q == 1) && !(j > 0
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

int	escaped_bslash(const char *str, int pos)
{
	int	backslash_count;

	backslash_count = 0;
	while (pos > 0 && str[pos] == '\\')
	{
		backslash_count++;
		pos--;
	}
	if (backslash_count % 2 == 0)
		return (1);
	return (0);
}
