/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_b.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:23:15 by prosas-p          #+#    #+#             */
/*   Updated: 2024/09/03 16:45:42 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_B_H
# define PHILOSOPHERS_B_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

# define RESET		"\x1b[0m"
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\033[0;36m"
# define YELLOW		"\033[0;33m"
# define MEDALLA	"🏅"

typedef struct s_table
{
	struct timeval	p_time;
	sem_t			*forks;
	sem_t			*wrt;
	int				t_d;
	int				t_e;
	int				t_s;
	int				n_p;
	int				n_meals;
}	t_table;

typedef struct s_chair
{
	pthread_mutex_t	eatlock;
	struct timeval	last_eat;
	t_table			*idata;
	int				id;
	pthread_mutex_t	padlock;
	int				pending_meals;
}	t_chair;

int		val_args_b(char **argv, int argc, t_table *i_data, int i);
void	philosopher(t_chair *philo, pid_t *pids);
long	get_milisecs(struct timeval *start);
void	*observer(void *arg);
int		print_lock(t_chair *philo, char *msg, int color);

#endif
