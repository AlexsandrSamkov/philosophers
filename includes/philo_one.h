#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h> // удалить
# include <errno.h> // удалить
# define MSG_ERR_MALLOC "maloc fail \xf0\x9f\x92\x80\n"
# define MSG_ERR_TIME "get time fail \xf0\x9f\x92\x80\n"
# define MSG_ERR_MUTEX "Mutex fail  \xf0\x9f\x92\x80\n"
# define MSG_FORK	"%lld %d has taken a fork \n"
# define MSG_FORK2	"%lld %d has taken a fork \n"
# define MSG_EAT	"%lld %d is eating \n"
# define MSG_SLEEP	"%lld %d sleeping \n"
# define MSG_THINK	"%lld %d is thinking \n"

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
	uint64_t	*time_to_start;
	unsigned	*start;
	uint64_t	*time_to_lust_meal;
	uint64_t	*eat;
	uint64_t	*fork1;
	uint64_t	*fork2;
	uint64_t	*sleep;
	uint64_t	*think;
} 				philosophers_t;

#endif