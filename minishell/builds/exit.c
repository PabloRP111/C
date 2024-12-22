/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:00:45 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/24 14:55:25 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	bash_exit(t_minis *minis, char **argv)
{
	int	i;

	i = 0;
	while (argv[i + 1] != NULL)
		i++;
	ft_putendl_fd("exit", 1);
	if (i == 0)
		exit(minis->status);
	if (i >= 1)
	{
		if (ft_isnumeric(argv[1]) == 0
			|| (long long)ft_atoi(argv[1]) > LLONG_MAX
			|| (long long)ft_atoi(argv[1]) < LLONG_MIN)
		{
			free_exit(minis);
			set_status(minis, "numeric argument required", 2);
			exit(2);
		}
		if (i == 1)
			exit(ft_atoi(argv[1]) % 256);
		else
			set_status(minis, "exit: too many arguments", 1);
	}
}
