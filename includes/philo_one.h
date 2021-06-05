#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define MSG_ERR_MALLOC "maloc fail \x55\x2b\x32\x36\x32\x30"
# define MSG_ERR_TIME "get time fail \x55\x2b\x32\x36\x32\x30"
typedef struct s_options
{

} 			t_options;

typedef struct s_philosopher {

} t_philosopher;

typedef struct s_all
{
	pthread_t tread_philosofer;
	pthread_mutex_t **forks;
	unsigned	left_fork;
	unsigned	right_fork;
	unsigned	death;
	unsigned	philo_nbr;
	unsigned 	time_to_die;
	unsigned 	time_to_eat;
	unsigned 	time_to_sleep;
	unsigned 	eat_nbr;
	uint64_t	last_meal;
	uint64_t	start;
}			t_all;


#endif