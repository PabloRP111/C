/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:20:43 by prosas-p          #+#    #+#             */
/*   Updated: 2024/09/09 12:49:46 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_b.h"

void	kill_all(t_table *i_data, pid_t *pids)
{
	int		i;

	i = -1;
	while (++i < i_data->n_p)
	{
		if (kill(pids[i], SIGKILL) == 1)
			printf("\nError to kill %d\n", i);
	}
}

int	destroy_sems(t_table *i_data)
{
	sem_close(i_data->forks);
	if (sem_unlink("/sem_forks") != 0)
		return (1);
	sem_close(i_data->wrt);
	if (sem_unlink("/sem_write") != 0)
		return (1);
	return (0);
}

int	wait_to_end(t_table *i_data, pid_t *pids)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (++i < i_data->n_p)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			kill_all(i_data, pids);
			sem_post(i_data->wrt);
			return (free(pids), destroy_sems(i_data), 1);
		}
	}
	free(pids);
	destroy_sems(i_data);
	if (i_data->n_meals != -1)
		printf(YELLOW "\nAll philosophers had eaten %d meals" MEDALLA RESET,
			i_data->n_meals);
	return (0);
}

void	create_sems(t_table *i_data, pid_t *pids)
{
	sem_unlink("/sem_forks");
	i_data->forks = sem_open("/sem_forks", O_CREAT | O_EXCL, 0644, i_data->n_p);
	if (i_data->forks == SEM_FAILED)
	{
		printf("\nsem_open failed\n");
		free(pids);
		exit(1);
	}
	sem_unlink("/sem_write");
	i_data->wrt = sem_open("/sem_write", O_CREAT | O_EXCL, 0644, 1);
	if (i_data->wrt == SEM_FAILED)
	{
		printf("\nsem_open failed\n");
		free(pids);
		exit(1);
	}
	if (gettimeofday(&i_data->p_time, NULL) != 0)
	{
		printf("\nget time failed\n");
		destroy_sems(i_data);
		free(pids);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_chair	philo;
	t_table	i_data;
	pid_t	*pids;
	int		i;

	if ((argc < 5 || argc > 6) || val_args_b(argv, argc, &i_data, 1) == 1)
		return (1);
	memset(&philo, 0, sizeof(t_chair));
	pids = malloc(i_data.n_p * sizeof(pid_t));
	if (!pids)
		return (printf("\nMalloc Error\n"), 1);
	create_sems(&i_data, pids);
	philo.idata = &i_data;
	i = -1;
	while (++i < i_data.n_p)
	{
		philo.id = i + 1;
		pids[i] = fork();
		if (pids[i] == -1)
			return (printf("\nError created proces\n"), free(pids), 1);
		if (pids[i] == 0)
			philosopher(&philo, pids);
	}
	return (wait_to_end(&i_data, pids));
}
