/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:31:50 by prosas-p          #+#    #+#             */
/*   Updated: 2024/09/03 15:28:47 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

long	get_milisecs(struct timeval *start)
{
	struct timeval	time;
	long			seconds;
	long			useconds;
	long			f_time;

	if (gettimeofday(&time, NULL) != 0)
		return (printf("\nWait error\n"), -1);
	seconds = time.tv_sec - start->tv_sec;
	useconds = time.tv_usec - start->tv_usec;
	if (useconds < 0)
	{
		seconds -= 1;
		useconds += 1000000;
	}
	f_time = (seconds * 1000) + (useconds / 1000);
	return (f_time);
}

int	print_lock(t_chair *philo, char *msg, int color)
{
	sem_wait(philo->idata->wrt);
	if (color == 1)
		printf(GREEN "%ld %d %s\n" RESET,
			get_milisecs(&philo->idata->p_time), philo->id, msg);
	else if (color == 2)
		printf(MAGENTA "%ld %d %s\n" RESET,
			get_milisecs(&philo->idata->p_time), philo->id, msg);
	else if (color == 3)
		printf(CYAN "%ld %d %s\n" RESET,
			get_milisecs(&philo->idata->p_time), philo->id, msg);
	else if (color == 4)
		printf(YELLOW "%ld %d %s\n" RESET,
			get_milisecs(&philo->idata->p_time), philo->id, msg);
	else
		printf("%s\n", msg);
	sem_post(philo->idata->wrt);
	return (0);
}
