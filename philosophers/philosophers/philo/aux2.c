/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:41:36 by prosas-p          #+#    #+#             */
/*   Updated: 2024/09/05 14:21:10 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_milisecs(long milisecs)
{
	struct timeval	st;
	struct timeval	time;
	long long		excedent;

	if ((gettimeofday(&st, NULL) != 0) || gettimeofday(&time, NULL) != 0)
	{
		printf("\nUncoordinate error\n");
		return ;
	}
	excedent = (time.tv_sec - st.tv_sec) * 1000000LL
		+ (time.tv_usec - st.tv_usec);
	while (excedent < (milisecs * 1000LL))
	{
		if (gettimeofday(&time, NULL) != 0)
		{
			printf("\nUncoordinate error\n");
			return ;
		}
		excedent = (time.tv_sec - st.tv_sec) * 1000000LL
			+ (time.tv_usec - st.tv_usec);
	}
}

void	wait_microsecs(long microsecs)
{
	struct timeval	st;
	struct timeval	time;
	long long		excedent;

	if ((gettimeofday(&st, NULL) != 0) || gettimeofday(&time, NULL) != 0)
	{
		printf("\nUncoordinate error\n");
		return ;
	}
	excedent = (time.tv_sec - st.tv_sec)
		+ (time.tv_usec - st.tv_usec);
	while (excedent < microsecs)
	{
		if (gettimeofday(&time, NULL) != 0)
		{
			printf("\nUncoordinate error\n");
			return ;
		}
		excedent = (time.tv_sec - st.tv_sec)
			+ (time.tv_usec - st.tv_usec);
	}
}

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

void	print_lock(t_chair *philo, char *msg, int color)
{
	pthread_mutex_lock(&philo->idata->deadlock);
	if (philo->idata->deads == 1)
	{
		pthread_mutex_unlock(&philo->idata->deadlock);
		return ;
	}
	pthread_mutex_lock(&philo->idata->wrt_lock);
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
	pthread_mutex_unlock(&philo->idata->wrt_lock);
	pthread_mutex_unlock(&philo->idata->deadlock);
}
