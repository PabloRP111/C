/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:50:07 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/22 15:02:03 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bash_echo_n(char **str, int *i)
{
	int	n;
	int	j;

	j = 0;
	n = 0;
	while (str[*i][0] == '-' && str[*i][j + 1] == 'n')
	{
		j++;
		if (str[*i][j + 1] == '\0')
		{
			*i += 1;
			j = 0;
			n = 1;
		}
	}
	return (n);
}

void	bash_echo(t_minis *minis, char **line)
{
	int		i;
	int		j;
	int		n;

	i = 1;
	change_int(&j, &n, 0, 0);
	if (!line || !line[1])
		write(1, "\n", 1);
	else
	{
		if (line[i][j] == '-' && (line[i][j + 1]) == 'n')
			n = bash_echo_n(line, &i);
		while (line[i])
		{
			while (line[i][j] != '\0')
				write (1, &line[i][j++], 1);
			if (empty_str(line[i + 1]) == 1)
				write (1, " ", 1);
			i++;
			j = 0;
		}
		if (n == 0)
			write(1, "\n", 1);
		set_status(minis, NULL, 0);
	}
}
