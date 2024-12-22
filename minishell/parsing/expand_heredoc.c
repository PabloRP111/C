/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:29:37 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/18 21:06:43 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	null_expand_h(t_minis *minis, int i, int j, int aux)
{
	char	*nl;

	decide_start_point(minis, &aux);
	if (minis->str_aux[i] && ft_isalpha(minis->str_aux[++i]) != 0)
		while (minis->str_aux[i] && ft_isalnum(minis->str_aux[i]) != 0)
			change_int(&i, &j, i + 1, j + 1);
	nl = calloc(ft_strlen(minis->str_aux) - j, sizeof(char));
	if (!nl)
		return (1);
	change_int(&i, &j, 0, 0);
	while (i++ < aux)
	{
		nl[j] = minis->str_aux[j];
		j++;
	}
	advance_to_dollar(nl, &aux);
	if (minis->str_aux[++aux] && ft_isalpha(minis->str_aux[aux]) == 1)
	{
		while (minis->str_aux[aux] && ft_isalnum(minis->str_aux[aux]) == 1)
			aux++;
	}
	else
		aux++;
	return (null_expand2_h(minis, &nl, j, aux));
}

int	expand_str_h(t_minis *minis, int i, int j, char *expand)
{
	char	*nl;
	int		z;

	if (empty_str(expand) != 1)
		return (null_expand_h(minis, i, 0, i));
	nl = calloc(ft_strlen(expand) + ft_strlen(minis->str_aux) + 1,
			sizeof(char));
	if (!nl)
		return (free2(&minis->str_aux, &expand), 1);
	while (++j < i)
		nl[j] = minis->str_aux[j];
	change_int(&i, &z, i + 1, -1);
	while (minis->str_aux[i] && is_dif_str(minis->str_aux[i]) != 0)
		i++;
	while (expand && expand[++z])
		nl[j++] = expand[z];
	if (minis->str_aux[i] == '\"')
		i++;
	while (minis->str_aux[i])
		nl[j++] = minis->str_aux[i++];
	nl[j] = '\0';
	free2(&minis->str_aux, &expand);
	minis->str_aux = nl;
	return (0);
}

int	get_expand2_h(t_minis *minis, char **ep, char *v_env, int i)
{
	int	i2;
	int	j;

	change_int(&i2, &j, 0, -1);
	while (minis->p_env && minis->p_env[++j])
	{
		if (ft_strncmp_equal(v_env, minis->p_env[j], ft_strlen(v_env)) == 0)
		{
			while (minis->p_env[j][i2] && minis->p_env[j][i2] != '=')
				i2++;
			if (minis->p_env[j][i2] != '=')
				return (free(v_env), 0);
			(*ep) = calloc(ft_strlen(minis->p_env[j]) + 1 - i2++, sizeof(char));
			while ((*ep) && minis->p_env[j][i2])
				(*ep)[minis->aux++] = minis->p_env[j][i2++];
			if (i == -1)
				(*ep)[minis->aux++] = '\"';
			(*ep)[minis->aux] = '\0';
			break ;
		}
	}
	return (free(v_env), 0);
}

int	get_expand_h(t_minis *minis, char *line, char **ep, int i)
{
	char	*v_env;
	int		j;
	int		i2;

	i2 = i;
	change_int(&minis->aux, &j, 0, 0);
	if (line[i2] && ft_isalpha(line[i2]) == 0)
		return (0);
	while (line[i2] && is_dif_str(line[i2]) != 0)
		change_int(&i2, &j, i2 + 1, j + 1);
	v_env = ft_substr(line, i, j);
	if (!v_env)
		return (1);
	if (line[i2] == '\"')
		i = -1;
	return (get_expand2_h(minis, ep, v_env, i));
}

int	expand_heredoc(t_minis *minis, char *line, char *expand, int i)
{
	while (line[++i])
	{
		if ((line[i] && line[i] == '\'') && in_dquo(line, &i, 0) != 0)
		{
			i++;
			advance_space(line, &i);
			while (line[i] && in_quo(line, &i, 0) == 0)
				i++;
			if (line[i])
				i++;
		}
		if (line[i] && (line[i] == '$'))
		{
			if (line[i + 1] == '?')
				expand = ft_itoa(minis->status);
			else if (get_expand_h(minis, line, &expand, i + 1) != 0)
				return (1);
			minis->str_aux = ft_strdup(line);
			if (expand_str_h(minis, i, -1, expand) == 0)
				return (free(line), 0);
			free(minis->str_aux);
		}
	}
	return (1);
}
