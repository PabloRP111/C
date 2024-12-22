/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femoreno <femoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:48:31 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/24 13:05:38 by femoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bash_pwd(t_minis *minis)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
		while (pwd[i] != '\0')
			write(1, &pwd[i++], 1);
	else
	{
		set_status(minis, "memory allocation failure", 77);
		return ;
	}
	write(1, "\n", 1);
	set_status(minis, NULL, 0);
	free(pwd);
}
