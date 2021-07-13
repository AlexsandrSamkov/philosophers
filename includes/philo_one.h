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

typedef struct options_s
{
	int		number_of_philosophers;
	unsigned 		time_to_die;
	unsigned 		time_to_eat;
	unsigned 		time_to_sleep;
	int		 		number_of_times_each_philosopher_must_eat;//
} options_t;

typedef struct philosophers_s
{
	int id;
	uint64_t time_to_start;
	uint64_t *time_to_lust_meat;
	pthread_mutex_t *forks;
	unsigned fork_left;
	unsigned fork_right;
	options_t *options;
	uint64_t *fork1;
	uint64_t *fork2;
	uint64_t *eat;
	uint64_t *sleep;
	uint64_t *think;
} 				philosophers_t;

#endif