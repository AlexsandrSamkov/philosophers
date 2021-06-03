#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <pthread.h>
typedef struct s_options
{
	int philo_nbr;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int eat_nbr;
	pthread_mutex_t *forks_right;
	pthread_mutex_t *forks_left;
} 			t_options;
#endif