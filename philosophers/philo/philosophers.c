/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:33:41 by prosas-p          #+#    #+#             */
/*   Updated: 2024/09/05 14:20:01 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	kill(t_chair *philos)
{
	pthread_mutex_lock(&(philos->idata->deadlock));
	pthread_mutex_lock(&(philos->idata->wrt_lock));
	printf(RED "\n%ld %d %s\n" RESET,
		get_milisecs(&philos->idata->p_time), philos->id, "is dead");
	philos->idata->deads = 1;
	pthread_mutex_unlock(&(philos->idata->wrt_lock));
	pthread_mutex_unlock(&(philos->idata->deadlock));
}

int	check_end(t_chair *philos)
{
	pthread_mutex_lock(&(philos->idata->padlock));
	if (philos->idata->p_finish == philos->idata->n_p)
		return (pthread_mutex_unlock(&(philos->idata->padlock)), 1);
	pthread_mutex_unlock(&(philos->idata->padlock));
	return (0);
}

void	*observer(void *arg)
{
	t_chair			*philos;

	philos = (t_chair *)arg;
	while (1)
	{
		pthread_mutex_lock(&(philos->idata->padlock));
		if (philos->finished != 1)
		{
			pthread_mutex_unlock(&(philos->idata->padlock));
			pthread_mutex_lock(&(philos->eat_lock));
			if (philos->last_eat.tv_usec != 0
				&& (get_milisecs(&philos->last_eat) >= philos->idata->t_d))
				return (pthread_mutex_unlock(&(philos->eat_lock)),
					kill(philos), NULL);
			pthread_mutex_unlock(&(philos->eat_lock));
		}
		else
			pthread_mutex_unlock(&(philos->idata->padlock));
		if ((philos->idata->n_meals != -1) && check_end(philos) == 1)
			return (NULL);
		philos = philos->next;
	}
}

void	wait_threads(t_chair *philos)
{
	pthread_t	watchmen;

	if (gettimeofday(&philos->idata->p_time, NULL) != 0)
		return ;
	pthread_mutex_lock(&philos->idata->start_lock);
	philos->idata->start = 1;
	pthread_mutex_unlock(&philos->idata->start_lock);
	if (pthread_create(&watchmen, NULL, observer, philos) != 0)
		return (free_and_exit(philos, "create watchmen"));
	if (pthread_join(watchmen, NULL) != 0)
		return (free_and_exit(philos, "wait watchmen"));
	if (philos->idata->p_finish == philos->idata->n_p)
		printf(YELLOW "\nAll phisophers have eaten %d meals %s\n" RESET,
			philos->idata->n_meals, MEDALLA);
	end_threads(philos);
}

int	main(int argc, char **argv)
{
	t_chair	*philos;
	t_table	i_data;
	int		i;

	if ((argc < 5 || argc > 6) || val_args(argv, argc, &i_data, 1) != 1)
		return (1);
	philos = malloc(i_data.n_p * sizeof(t_chair));
	if (!philos)
		return (printf("\nMalloc Error\n"), 1);
	if (init_vals(&i_data, &i) == 0)
		return (printf("\nError init variables\n"), 1);
	while (++i < i_data.n_p)
	{
		memset(&philos[i], 0, sizeof(t_chair));
		philos[i].id = i + 1;
		philos[i].idata = &i_data;
		if ((pthread_mutex_init(&philos[i].fork, NULL) != 0)
			|| (pthread_mutex_init(&philos[i].eat_lock, NULL) != 0))
			return (free_and_exit(philos, "init fork"), 1);
		philos[i].next = &philos[(i + 1) % i_data.n_p];
		philos[i].prev = &philos[(i - 1 + i_data.n_p) % i_data.n_p];
		if (pthread_create(&philos[i].philo, NULL, philo_f, &philos[i]) != 0)
			return (free_and_exit(philos, "create thread"), 1);
	}
	wait_threads(philos);
}
