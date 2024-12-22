/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:49:41 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/22 11:30:44 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	metasim(char *line, int *i, int sum, int con)
{
	if (line == NULL || line[*i] == '\0')
		return (-1);
	if (*i > 0 && line[*i - 1] == '\\' && escaped_bslash(line, *i - 1) == 0)
		;
	else if (in_quo(line, i, 0) == 0)
		;
	else if (((line[*i] == '>') && (line[*i + 1] == '>'))
		|| ((line[*i] == '<') && (line[*i + 1] == '<')))
	{
		if (sum == 0 && con == 1)
			*i += 2;
		return (1);
	}
	else if (((line[*i] == '>') || (line[*i] == '<')))
	{
		if (sum == 0 && con == 0)
			*i += 1;
		return (0);
	}
	else if (line[*i] == '|')
		return (2);
	if (sum == 0 && con == 3)
		*i += 1;
	return (3);
}

int	ft_strncmp_equal(const char *s1, const char *s2, size_t n)
{
	unsigned char	uc1;
	unsigned char	uc2;
	size_t			i;

	i = 0;
	while (s1[i] == s2[i] && i < n)
	{
		uc1 = (unsigned char)s1[i];
		uc2 = (unsigned char)s2[i];
		if (uc1 == '\0')
			return (0);
		i++;
	}
	if (i == n && s1[i] == '\0' && s2[i] != '=')
		return (1);
	if (s1[i] != s2[i] && i < n)
	{
		uc1 = (unsigned char)s1[i];
		uc2 = (unsigned char)s2[i];
		return (uc1 - uc2);
	}
	return (0);
}

void	advance_to_dollar(char	*str, int *aux)
{
	if (!str || !str[*aux])
		return ;
	while (str[*aux] && str[*aux] != '$')
		*aux += 1;
}

void	free_change_p(char **str, char **new_str, int *z, int *i)
{
	if (!str || !new_str || !(*str) || !(*new_str))
		return ;
	free(*str);
	(*str) = (*new_str);
	new_str = NULL;
	change_int(z, i, -1, *i - 2);
}

void	free_final(t_minis *minis)
{
	if (minis->p_env)
		free_matrix_twice(minis->p_env);
	if (minis->path_here_doc)
		free(minis->path_here_doc);
	minis->path_here_doc = NULL;
}
