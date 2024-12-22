/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prosas-p <prosas-p@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:34:17 by prosas-p          #+#    #+#             */
/*   Updated: 2024/09/04 17:55:54 by prosas-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

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
	int				deads;
	pthread_mutex_t	deadlock;
	int				p_finish;
	pthread_mutex_t	padlock;
	pthread_mutex_t	wrt_lock;
	pthread_mutex_t	start_lock;
	int				start;
	int				n_meals;
	int				t_d;
	int				t_e;
	int				t_s;
	int				n_p;
}	t_table;

typedef struct s_chair
{
	struct timeval	last_eat;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	fork;
	pthread_t		philo;
	struct s_chair	*next;
	struct s_chair	*prev;
	t_table			*idata;
	int				id;
	int				finished;
	int				pending_meals;
}	t_chair;

long	get_milisecs(struct timeval *start);
int		init_vals(t_table *i_data, int *i);
int		val_args(char **argv, int argc, t_table *i_data, int i);
void	free_and_exit(t_chair *philos, char *error);
void	print_lock(t_chair *philo, char *msg, int color);
void	wait_microsecs(long microsecs);
void	wait_milisecs(long milisecs);
void	end_threads(t_chair *philos);
void	*philo_f(void *arg);
int		lonely_boy(t_table *i_data);

#endif
