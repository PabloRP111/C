/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femoreno <femoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:06:18 by prosas-p          #+#    #+#             */
/*   Updated: 2024/11/25 18:10:01 by femoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	advance_str(char *str, char c, int *i)
{
	if (!str)
		return ;
	if (str[*i] == c)
		*i += 1;
}

int	add_var2(t_minis *minis, char **name, int *i, int z)
{
	while (minis->p_env[++(*i)])
	{
		if ((int)ft_strlenc(minis->p_env[(*i)], '=') >= z)
			z = ft_strlenc(minis->p_env[(*i)], '=');
		if (ft_strncmp(minis->p_env[(*i)], (*name), z) == 0)
			return (free((*name)), 1);
		z = ft_strlen((*name));
	}
	free((*name));
	return (0);
}
