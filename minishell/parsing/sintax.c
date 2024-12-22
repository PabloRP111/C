/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sintax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:41:22 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/25 17:34:06 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_wrong(char *str, int i)
{
	char	c;

	c = str[i];
	if (in_quo(str, &i, 0) == 0)
		return (0);
	if (c == '|')
		return (2);
	if (c == '<' || c == '>')
		return (3);
	if (c == '&' || c == '#' || c == '(' || c == ')' || c == '[' || c == ']'
		|| c == '{' || c == '}')
		return (1);
	return (0);
}

int	is_wrong_redir(char *redir, int i)
{
	if (redir[i + 2] == '<' || redir[i + 2] == '>')
		return (2);
	if (redir[i] == '<' && redir[i + 1] == '>')
		return (1);
	if (redir[i] == '>' && redir[i + 1] == '<')
		return (1);
	if (redir[i + 1] == '<' || redir[i + 1] == '>')
		i += 2;
	else
		i++;
	advance_space(redir, &i);
	if (redir[i] == '\0' || is_wrong(redir, i) != 0)
		return (i);
	return (0);
}

int	strange_character(t_minis *minis, int i)
{
	while (minis->line[i])
	{
		if (is_wrong(minis->line, i) == 2)
		{
			i++;
			advance_space(minis->line, &i);
			if (!minis->line[i])
				break ;
			if (check_pipes(minis, i) == 1)
				return (1);
		}
		else if (is_wrong(minis->line, i) == 3)
		{
			if (is_wrong_redir(minis->line, i) != 0)
				return (set_status(minis,
						"syntax error near unexpected token `<>'\n", 2), 1);
		}
		else if (is_wrong(minis->line, i) == 1)
			return (set_status(minis,
					"syntax error near unexpected token `&#()[]{}'\n", 2), 1);
		i++;
	}
	return (0);
}
