/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 07:55:41 by prosas-p          #+#    #+#             */
/*   Updated: 2024/09/04 17:55:36 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_f(t_chair *philo)
{
	pthread_mutex_lock(&philo->idata->start_lock);
	if (philo->idata->start == 1)
		return (pthread_mutex_unlock(&philo->idata->start_lock), 1);
	pthread_mutex_unlock(&philo->idata->start_lock);
	return (0);
}

void	leave_forks(t_chair *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->prev)->fork);
	}
	else
	{
		pthread_mutex_unlock(&(philo->prev)->fork);
		pthread_mutex_unlock(&(philo->fork));
	}
}

void	get_forks(t_chair *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->fork));
		print_lock(philo, "is taking a left fork", 1);
		pthread_mutex_lock(&(philo->prev)->fork);
		print_lock(philo, "is taking a rigth fork", 1);
	}
	else
	{
		pthread_mutex_lock(&(philo->prev)->fork);
		print_lock(philo, "is taking a rigth fork", 1);
		pthread_mutex_lock(&(philo->fork));
		print_lock(philo, "is taking a left fork", 1);
	}
	pthread_mutex_lock(&philo->eat_lock);
	print_lock(philo, "is eaten", 4);
	gettimeofday(&philo->last_eat, NULL);
	pthread_mutex_unlock(&philo->eat_lock);
	usleep(philo->idata->t_e * 1000);
	leave_forks(philo);
}

void	try_eat(t_chair *philo)
{
	get_forks(philo);
	if (philo->pending_meals == 1)
	{
		pthread_mutex_lock(&philo->idata->padlock);
		philo->idata->p_finish += 1;
		philo->finished = 1;
		pthread_mutex_unlock(&philo->idata->padlock);
		return ;
	}
	print_lock(philo, "is sleeping", 2);
	usleep(philo->idata->t_s * 1000);
	print_lock(philo, "is thinking", 3);
	usleep(150);
	return ;
}

void	*philo_f(void *arg)
{
	t_chair	*philo;
	int		meals;

	philo = (t_chair *)arg;
	meals = philo->idata->n_meals;
	while (start_f(philo) == 0)
		;
	if (philo->id % 2 != 0)
		usleep(philo->idata->t_e * 1000);
	while (1)
	{
		philo->pending_meals = meals;
		try_eat(philo);
		pthread_mutex_lock(&philo->idata->deadlock);
		if (philo->idata->deads != 0)
			return (pthread_mutex_unlock(&philo->idata->deadlock), NULL);
		pthread_mutex_unlock(&philo->idata->deadlock);
		if (meals > 0)
			meals--;
		if (meals == 0)
			break ;
	}
	return (NULL);
}
