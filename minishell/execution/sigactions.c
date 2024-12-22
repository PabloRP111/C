/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigactions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:52:20 by femoreno          #+#    #+#             */
/*   Updated: 2024/11/25 17:08:27 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_childsignal(int sn)
{
	(void)sn;
	write(1, "\n", 1);
	g_sig = 1;
}

void	ms_setsignalson(void)
{
	struct sigaction	signal1;
	struct sigaction	signal2;

	ft_memset(&signal2, 0, sizeof(signal2));
	signal2.sa_handler = &ms_childsignal;
	signal2.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signal2, NULL);
	ft_memset(&signal1, 0, sizeof(signal1));
	signal1.sa_handler = &signal_quit_children;
	signal1.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &signal1, NULL);
}

void	ms_setsignals(void)
{
	struct sigaction	signal;

	ft_memset(&signal, 0, sizeof(signal));
	signal.sa_handler = &handle_sigint;
	signal.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signal, NULL);
	signal.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal, NULL);
}

void	ms_setsignalhere(void)
{
	struct sigaction	signal;

	ft_memset(&signal, 0, sizeof(signal));
	signal.sa_handler = &handle_sigint2;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}

void	ms_setsignal2(void)
{
	struct sigaction	signal;

	ft_memset(&signal, 0, sizeof(signal));
	signal.sa_handler = &handle_sigint3;
	signal.sa_flags = SA_RESTART;
	sigaction(SIGINT, &signal, NULL);
	signal.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &signal, NULL);
}
