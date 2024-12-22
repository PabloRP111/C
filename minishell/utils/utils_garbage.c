/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_garbage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:31:13 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/15 10:18:59 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free2(char **str, char **str2)
{
	if (*str != NULL)
		free(*str);
	if (*str2 != NULL)
		free(*str2);
}

void	add_null(char *c1, char *c2)
{
	if (c1 != NULL)
		*c1 = '\0';
	if (c2 != NULL)
		*c2 = '\0';
}

int	empty_str(char *str)
{
	if (str == NULL)
		return (-1);
	if (str[0] == '\0')
		return (0);
	return (1);
}

void	advance_space(char *str, int *i)
{
	while (str[*i] == ' ' || str[*i] == '\t' || str[*i] == '\v'
		|| str[*i] == '\n' || str[*i] == '\r' || str[*i] == '\f')
		*i += 1;
}

void	add2(t_minis *minis, int red, int *lp, int *i2)
{
	minis->cmds->redir[red][*i2] = minis->line[*lp];
	change_int(i2, lp, *i2 + 1, *lp + 1);
	minis->cmds->redir[red][*i2] = minis->line[*lp];
	change_int(i2, lp, *i2 + 1, *lp + 1);
}
