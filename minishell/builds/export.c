/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:27:12 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/25 17:11:03 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copymatriz(t_minis *minis, int n)
{
	int		i;
	int		j;
	char	**mtz;

	change_int(&i, &j, 0, -1);
	while (minis->p_env[i])
		i++;
	mtz = ft_calloc((i + 1 + n), sizeof(char *));
	if (!mtz)
		return (set_status(minis, "memory allocation failure", 77), NULL);
	while (++j < i)
		mtz[j] = ft_strdup(minis->p_env[j]);
	mtz[j] = NULL;
	return (mtz);
}

void	writecom(char *str)
{
	int	i;
	int	com;

	i = 0;
	com = 1;
	write (1, "declare -x ", 11);
	while (str[i])
	{
		write(1, &str[i], 1);
		if (str[i] == '=' && com == 1)
		{
			write(1, "\"", 1);
			com = 0;
		}
		if (str[i + 1] == '\0' && com == 0)
			write(1, "\"", 1);
		i++;
	}
	write(1, "\n", 1);
}

void	smallest(t_minis *minis)
{
	char	**vars;
	int		i;
	int		m;

	vars = copymatriz(minis, 1);
	while (vars[0])
	{
		change_int(&i, &m, -1, 0);
		while (vars[++i])
			if (ft_strncmp(vars[m], vars[i], ft_strlen(vars[i])) > 0)
				m = i;
		if (ft_isalpha(vars[m][0]) == 1)
			writecom(vars[m]);
		free(vars[m]);
		m--;
		while (vars[++m + 1])
			vars[m] = vars[m + 1];
		vars[m] = NULL;
	}
	free(vars);
}

void	bash_export_2(t_minis *minis, char **str)
{
	int	i;
	int	correct;

	i = 1;
	correct = 0;
	while (str[i])
	{
		correct = bash_correct_export_arg(minis, str[i]);
		if (correct == 1)
			if (replace_var(minis, str[i]) == 1)
				add_var(minis, str[i], -1);
		if (correct == 0)
			append_var(minis, str[i]);
		i++;
	}
}

void	bash_export(t_minis *minis, char **str)
{
	if (str && !str[1])
		smallest(minis);
	else
		bash_export_2(minis, str);
}
