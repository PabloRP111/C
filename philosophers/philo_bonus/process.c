/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:59:31 by prosas-p          #+#    #+#             */
/*   Updated: 2024/09/09 12:46:15 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

void	eat(t_chair *philo)
{
	sem_wait(philo->idata->forks);
	print_lock(philo, "is taking a fork", 1);
	sem_wait(philo->idata->forks);
	print_lock(philo, "is taking a fork", 1);
	pthread_mutex_lock(&philo->eatlock);
	print_lock(philo, "is eaten", 4);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&philo->eatlock);
	usleep(philo->idata->t_e * 1000);
	sem_post(philo->idata->forks);
	sem_post(philo->idata->forks);
}

void	try_eat(t_chair *philo)
{
	while (1)
	{
		usleep(50);
		eat(philo);
		if (philo->idata->n_meals > 0)
		{
			pthread_mutex_lock(&philo->padlock);
			if (philo->pending_meals > 0)
				philo->pending_meals--;
			if (philo->pending_meals == 0)
			{
				pthread_mutex_unlock(&philo->padlock);
				return ;
			}
			pthread_mutex_unlock(&philo->padlock);
		}
		print_lock(philo, "is sleeping", 2);
		usleep(philo->idata->t_s * 1000);
		print_lock(philo, "is thinking", 3);
	}
}

void	lonely_boy(t_chair *philo)
{
	sem_wait(philo->idata->forks);
	print_lock(philo, "is taking a fork", 1);
	usleep(philo->idata->t_d * 1000);
	sem_wait(philo->idata->wrt);
	printf(RED "%ld %d has died\n" RESET,
		get_milisecs(&philo->idata->p_time), philo->id);
	sem_post(philo->idata->wrt);
	sem_post(philo->idata->forks);
	sem_close(philo->idata->forks);
	exit(0);
}

void	philosopher(t_chair *philo, pid_t *pids)
{
	pthread_t	watchmen;

	free(pids);
	if (philo->idata->n_p == 1)
		lonely_boy(philo);
	philo->pending_meals = philo->idata->n_meals;
	if ((pthread_mutex_init(&philo->eatlock, NULL) != 0)
		|| (pthread_mutex_init(&philo->padlock, NULL) != 0))
		exit(1);
	if (pthread_create(&watchmen, NULL, observer, philo) != 0)
		exit(1);
	try_eat(philo);
	if (pthread_join(watchmen, NULL) != 0)
		exit(1);
	exit(0);
}
