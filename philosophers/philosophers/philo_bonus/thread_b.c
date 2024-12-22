/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 09:44:36 by prosas-p          #+#    #+#             */
/*   Updated: 2024/09/04 17:59:26 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

void	end_process(t_chair *philo)
{
	sem_wait(philo->idata->wrt);
	printf(RED "%ld %d has died\n" RESET,
		get_milisecs(&philo->idata->p_time), philo->id);
	sem_close(philo->idata->wrt);
	sem_close(philo->idata->forks);
	exit(1);
}

void	*observer(void *arg)
{
	t_chair			*philo;

	philo = (t_chair *)arg;
	while (1)
	{
		usleep(150);
		pthread_mutex_lock(&philo->eatlock);
		if (philo->last_eat.tv_usec != 0
			&& (get_milisecs(&philo->last_eat) >= philo->idata->t_d))
		{
			pthread_mutex_unlock(&philo->eatlock);
			end_process(philo);
		}
		else
			pthread_mutex_unlock(&philo->eatlock);
		pthread_mutex_lock(&philo->padlock);
		if (philo->pending_meals == 0)
		{
			pthread_mutex_unlock(&philo->padlock);
			break ;
		}
		pthread_mutex_unlock(&philo->padlock);
	}
	return (NULL);
}
