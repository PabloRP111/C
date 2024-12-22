/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:57:11 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/25 17:09:24 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reopen_fd(void)
{
	int	fd;

	if (access("/dev/tty", R_OK) == 0)
	{
		fd = open("/dev/tty", O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
}

void	handle_sigint2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_sig = 1;
	close(STDIN_FILENO);
}

void	signal_cd_heredoc(char *name, int i)
{
	printf("%s%d%s%s%s\n",
		"warning: here-document at line ", i,
		" delimited by end-of-file (wanted `", name, "')");
}

void	signal_cd_quotes(char quotes)
{
	printf("%s%c%s\n", "unexpected EOF while looking for matching `",
		quotes, "'");
	printf("%s\n", "syntax error: unexpected end of file");
}

void	signal_quit_children(int signum)
{
	(void)signum;
	write(1, "Quit (core dumped)\n", 19);
	g_sig = 1;
}
