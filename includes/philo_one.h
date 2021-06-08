#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define MSG_ERR_MALLOC "maloc fail \x55\x2b\x32\x36\x32\x30\n"
# define MSG_ERR_TIME "get time fail \x55\x2b\x32\x36\x32\x30\n"
# define MSG_ERR_MUTEX "Mutex fail  \x55\x2b\x32\x36\x32\x30\n"
# define MSG_FORK	"%lld %d has taken a fork %u \xf0\x9f\xa5\x84\n"
# define MSG_FORK2	"%lld %d has taken a fork %u \xf0\x9f\x94\xaa\n"
# define MSG_EAT	"%lld %d is eating \xf0\x9f\x8d\x9c\n"
# define MSG_SLEEP	"%lld %d sleeping \xf0\x9f\x9b\x8c\n"
# define MSG_THINK	"%lld %d is thinking \xf0\x9f\xa4\x94\n"

typedef struct philosophers_s
{
	int 	nbr_ph;
	unsigned 	time_to_die;
	unsigned 	time_to_eat;
	unsigned 	time_to_sleep;
	unsigned 	fork_left;
	unsigned 	fork_right;
	unsigned 	id;
	unsigned 	number_of_cycles;
	pthread_mutex_t **forks;
	pthread_mutex_t *waiter;
	uint64_t	time_to_start;
	uint64_t	*time_to_lust_meal;
} 				philosophers_t;

#endif