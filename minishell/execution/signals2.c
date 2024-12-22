/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:07:16 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/24 17:23:41 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_cd_pipes(void)
{
	printf("%s\n", "syntax error: unexpected end of file");
	exit(2);
}

void	handle_sigint3(int sig)
{
	(void)sig;
	g_sig = 1;
	write(1, "\n", 1);
	rl_on_new_line();
}

void	handle_sigint(int sig)
{
	g_sig = sig;
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
