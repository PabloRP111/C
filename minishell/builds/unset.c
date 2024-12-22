/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femoreno <femoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 09:51:06 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/25 17:53:51 by femoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bash_unset_2(t_minis *minis, char *str)
{
	int		i;
	int		j;
	int		z;

	change_int(&i, &j, 0, -1);
	i = ft_strlenc(str, '=');
	z = i;
	while (minis->p_env[++j])
	{
		if ((int)ft_strlenc(minis->p_env[j], '=') >= i)
			z = ft_strlenc(minis->p_env[j], '=');
		if (ft_strncmp(minis->p_env[j], str, z) == 0)
			break ;
		z = i;
	}
	if (!minis->p_env[j])
		return ;
	free(minis->p_env[j]);
	while (minis->p_env[++j])
		minis->p_env[j - 1] = minis->p_env[j];
	minis->p_env[j - 1] = NULL;
}

void	bash_unset(t_minis *minis, char **str)
{
	int		i;

	i = 0;
	while (str[++i])
		bash_unset_2(minis, str[i]);
	set_status(minis, NULL, 0);
}
