/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:31:41 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/24 17:19:19 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	incomplete_text(t_minis *minis, char **line, char quotes)
{
	char	*str;
	char	*text;

	signal(SIGINT, handle_sigint2);
	*line = readline("> ");
	if (!(*line) && g_sig == 0)
	{
		signal_cd_quotes(quotes);
		return (1);
	}
	str = *line;
	*line = ft_strjoin("\n", *line);
	if (!(*line))
		return (1);
	free(str);
	str = NULL;
	text = ft_strjoin(minis->line, *line);
	if (!text)
		return (1);
	free2(&minis->line, line);
	line = NULL;
	minis->line = text;
	text = NULL;
	return (0);
}

int	close_quoetes(t_minis *minis, int i, char quotes)
{
	char	*line;

	while (1)
	{
		i--;
		while (minis->line[++i])
		{
			if ((minis->line[i] == '\"' || minis->line[i] == '\'') && !(i > 0
					&& minis->line[i - 1] == '\\'
					&& escaped_bslash(minis->line, i - 1) == 0))
			{
				if (quotes == minis->line[i])
					quotes = 'q';
				else if (quotes == 'q')
					quotes = minis->line[i];
			}
		}
		if (quotes == 'q')
			break ;
		else if (incomplete_text(minis, &line, quotes) != 0)
			return (1);
	}
	return (0);
}

int	incomplete_pipe(t_minis *minis, char **line, int *i)
{
	char	*text;
	char	*aux;

	aux = NULL;
	signal(SIGINT, handle_sigint2);
	*line = readline("> ");
	if (!(*line) && g_sig == 0)
		signal_cd_pipes();
	if (*line && *line[0] != '\0')
		aux = ft_strjoin(" ", *line);
	free(*line);
	if (!aux)
		return (1);
	text = ft_strjoin(minis->line, aux);
	free2(&minis->line, &aux);
	if (!text)
		return (1);
	line = NULL;
	minis->line = text;
	text = NULL;
	*i = -1;
	return (0);
}

int	check_pipes(t_minis *minis, int i)
{
	if (minis->line[0] == '|')
	{
		if (minis->line[1] == '|')
			return (set_status(minis,
					"syntax error near unexpected token `||'", 2), 1);
		return (set_status(minis,
				"syntax error near unexpected token `|'", 2), 1);
	}
	if (minis->line[i] == '|' && in_quo(minis->line, &i, 0) != 0)
	{
		if (minis->line[i - 1] == '|')
			return (set_status(minis,
					"syntax error near unexpected token `||'", 2), 1);
		else
			return (set_status(minis,
					"syntax error near unexpected token `|'", 2), 1);
	}
	return (0);
}

int	close_pipes(t_minis *minis, int i)
{
	char	*line;

	while (1)
	{
		while (minis->line[i])
		{
			if (minis->line[i] == '|')
			{
				i++;
				advance_space(minis->line, &i);
				if (check_pipes(minis, i) != 0)
					return (1);
				if (minis->line[i] != '\0')
					break ;
				else if (minis->line[i] == '\0'
					&& incomplete_pipe(minis, &line, &i) != 0)
					return (1);
			}
			i++;
		}
		if (!minis->line[i])
			break ;
	}
	return (0);
}
