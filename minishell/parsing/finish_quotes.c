/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:10:53 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/11 20:20:29 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	clean_quotes_r(char **str, int i, int z, char q)
{
	char	*new_str;
	int		j;
	int		k;

	while ((*str)[++i])
	{
		if ((((*str)[i] == '\'') || ((*str)[i] == '\"')) && !(i - 1 > 0
			&& (*str)[i - 1] == '\\' && escaped_bslash((*str), i - 1) == 0))
		{
			q = (*str)[i];
			change_int(&j, &k, i++, -1);
			while ((*str)[i] && !((*str)[i] == q && !(i > 0
				&& (*str)[i - 1] == '\\' && escaped_bslash(*str, i - 1) == 0)))
				i++;
			new_str = (char *)ft_calloc(ft_strlen(*str) - 1, sizeof(char));
			if (!new_str)
				return (1);
			while (++k < (int)(ft_strlen(*str)) + 1)
				if (k != i && k != j)
					new_str[++z] = (*str)[k];
			free_change_p(str, &new_str, &z, &i);
		}
	}
	return (0);
}

int	clean_quotes(char **str, int i, int z, char q)
{
	char	*new_str;
	int		j;
	int		k;

	while ((*str)[++i])
	{
		if ((((*str)[i] == '\'') || ((*str)[i] == '\"')) && !(i > 0
			&& (*str)[i - 1] == '\\' && escaped_bslash((*str), i - 1) == 0))
		{
			q = (*str)[i];
			change_int(&j, &k, i++, -1);
			while (!((*str)[i] == q && !(i > 0 && (*str)[i - 1] == '\\'
				&& escaped_bslash((*str), i - 1) == 0)))
				i++;
			new_str = (char *)ft_calloc(ft_strlen(*str) - 1, sizeof(char));
			if (!new_str)
				return (1);
			while (++k < (int)(ft_strlen(*str)) + 1)
				if (k != i && k != j)
					new_str[++z] = (*str)[k];
			free_change_p(str, &new_str, &z, &i);
		}
	}
	return (0);
}

void	clean_backslash2(char **str, char **n_l, int *i, int bslash_p)
{
	free((*str));
	(*str) = *n_l;
	*i = bslash_p;
	while ((*str)[*i] == '\\')
		*i = *i + 1;
	if ((*str)[*i - 1] == '\\')
		*i = *i - 1;
}

int	clean_backslash(char **str, int i, int bslash_c, int bslash_p)
{
	char	*n_l;
	int		j;

	while ((*str)[++i])
	{
		if ((*str)[i] == '\\')
		{
			change_int(&bslash_p, &j, i, -1);
			while ((*str)[i] == '\\')
				change_int(&bslash_c, &i, bslash_c + 1, i + 1);
			n_l = ft_calloc(ft_strlen(*str) + 1 - (bslash_c % 2), sizeof(char));
			if (!n_l)
				return (1);
			while (++j < bslash_p)
				n_l[j] = (*str)[j];
			bslash_c /= 2;
			while (bslash_c-- > 0)
				n_l[j++] = '\\';
			while ((*str)[i])
				n_l[j++] = (*str)[i++];
			n_l[j] = '\0';
			clean_backslash2(str, &n_l, &i, bslash_p);
		}
	}
	return (0);
}

int	clean_unnecessary(t_minis *minis, int i, int j)
{
	while (minis->cmds && ++j < minis->n_cmd)
	{
		i = 0;
		while (minis->cmds[j].cmd && minis->cmds[j].cmd[i])
		{
			if (clean_quotes(&(minis->cmds[j].cmd[i]), -1, -1, 'q') != 0)
				return (1);
			if (clean_backslash(&(minis->cmds[j].cmd[i]), -1, 0, 0) != 0)
				return (1);
			i++;
		}
		i = 0;
		while (minis->cmds[j].redir && minis->cmds[j].redir[i])
		{
			if (clean_quotes_r(&(minis->cmds[j].redir[i]), -1, -1, 'q') != 0)
				return (1);
			if (clean_backslash(&(minis->cmds[j].redir[i]), -1, 0, 0) != 0)
				return (1);
			i++;
		}
	}
	return (0);
}
