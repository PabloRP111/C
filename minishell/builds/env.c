/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femoreno <femoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:18:06 by femoreno          #+#    #+#             */
/*   Updated: 2024/10/16 12:38:38 by femoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bash_env(t_minis *minis)
{
	int	i;
	int	j;

	i = 0;
	while (minis->p_env[i])
	{
		j = 0;
		while (minis->p_env[i][j])
		{
			if (minis->p_env[i][j] == '=')
			{
				j = 0;
				while (minis->p_env[i][j])
				{
					write(1, &minis->p_env[i][j], 1);
					j++;
				}
				write(1, "\n", 1);
				break ;
			}
			j++;
		}
		i++;
	}
	set_status(minis, NULL, 0);
}
