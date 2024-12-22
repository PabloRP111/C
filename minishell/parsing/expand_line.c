/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:33:29 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/22 16:06:30 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	null_expand(t_minis *minis, int i, int j, int aux)
{
	char	*nl;

	decide_start_point(minis, &aux);
	if (minis->line[i] && ft_isalpha(minis->line[++i]) != 0)
		while (minis->line[i] && ft_isalnum(minis->line[i]) != 0)
			change_int(&i, &j, i + 1, j + 1);
	nl = calloc(ft_strlen(minis->line) - j, sizeof(char));
	if (!nl)
		return (1);
	change_int(&i, &j, 0, 0);
	while (i++ < aux)
	{
		nl[j] = minis->line[j];
		j++;
	}
	advance_to_dollar(nl, &aux);
	if (minis->line[++aux] && ft_isalpha(minis->line[aux]) == 1)
	{
		while (minis->line[aux] && ft_isalnum(minis->line[aux]) == 1)
			aux++;
	}
	else
		aux++;
	return (null_expand2(minis, &nl, j, aux));
}

int	expand_str(t_minis *minis, int i, int j, char **expand)
{
	char	*nl;
	int		z;

	if (!(*expand) || (empty_str(*expand) == 0))
		return (null_expand(minis, i, 0, i));
	nl = calloc(ft_strlen(*expand) + ft_strlen(minis->line) + 1,
			sizeof(char));
	if (!nl)
		return (free2(&minis->line, expand), 1);
	while (++j < i)
		nl[j] = minis->line[j];
	change_int(&i, &z, i + 1, -1);
	while (minis->line[i] && is_dif_str(minis->line[i]) != 0)
		i++;
	advance_str(minis->line, '?', &i);
	while (expand && (*expand) && (*expand)[++z])
		nl[j++] = (*expand)[z];
	advance_str(minis->line, '\"', &i);
	while (minis->line[i])
		nl[j++] = minis->line[i++];
	nl[j] = '\0';
	free2(&minis->line, expand);
	minis->line = nl;
	return (0);
}

int	get_expand2(t_minis *minis, char **ep, char **v_env, int i)
{
	int	i2;
	int	j;

	change_int(&i2, &j, 0, -1);
	while (minis->p_env && minis->p_env[++j])
	{
		if (ft_strncmp_equal(*v_env, minis->p_env[j], ft_strlen(*v_env)) == 0)
		{
			while (minis->p_env[j][i2] && minis->p_env[j][i2] != '=')
				i2++;
			if (minis->p_env[j][i2] != '=')
				return (free(*v_env), 0);
			(*ep) = calloc(ft_strlen(minis->p_env[j]) + 1 - i2++, sizeof(char));
			while ((*ep) && minis->p_env[j][i2])
				(*ep)[minis->aux++] = minis->p_env[j][i2++];
			if (i == -1)
				(*ep)[minis->aux++] = '\"';
			(*ep)[minis->aux] = '\0';
			break ;
		}
	}
	return (free(*v_env), 0);
}

int	get_expand(t_minis *minis, char **ep, int i, int i2)
{
	char	*v_env;
	int		j;

	if (minis->line[i] == '?')
	{
		*ep = ft_itoa(minis->status);
		return (0);
	}
	change_int(&minis->aux, &j, 0, 0);
	if (minis->line[i2] && ft_isalpha(minis->line[i2]) == 0)
		return (0);
	while (minis->line[i2] && is_dif_str(minis->line[i2]) != 0)
		change_int(&i2, &j, i2 + 1, j + 1);
	v_env = ft_substr(minis->line, i, j);
	if (!v_env)
		return (1);
	if (minis->line[i2] == '\"')
		i = -1;
	return (get_expand2(minis, ep, &v_env, i));
}

int	expand(t_minis *minis, int i, int j, char *expand)
{
	while (minis->line[i])
	{
		if (minis->line[i] && minis->line[i] == '\''
			&& in_dquo(minis->line, &i, 0) != 0)
		{
			i++;
			advance_space(minis->line, &i);
			while (minis->line[i] && in_quo(minis->line, &i, 0) == 0)
				i++;
			if (minis->line[i] && minis->line[i] == '\'')
				i++;
		}
		if (minis->line[i] && minis->line[i] == '$'
			&& its_expand(minis->line, &i) == 0)
		{
			if (get_expand(minis, &expand, i + 1, i + 1) != 0)
				return (1);
			if (expand_str(minis, i, j, &expand) != 0)
				return (1);
		}
		if (minis->line[i])
			i++;
	}
	return (0);
}
