#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define MSG_ERR_MALLOC "maloc fail \x55\x2b\x32\x36\x32\x30\n"
# define MSG_ERR_TIME "get time fail \x55\x2b\x32\x36\x32\x30\n"
# define MSG_ERR_MUTEX "Mutex fail  \x55\x2b\x32\x36\x32\x30\n"
# define MSG_FORK	"%lld %d has taken a fork \xf0\x9f\xa5\x84\n"
# define MSG_FORK2	"%lld %d has taken a fork \xf0\x9f\x94\xaa\n"
# define MSG_EAT	"%lld %d is eating \xf0\x9f\x8d\x9c\n"
# define MSG_SLEEP	"%lld %d sleeping \xf0\x9f\x9b\x8c\n"
# define MSG_THINK	"%lld %d is thinking \xf0\x9f\xa4\x94\n"
typedef struct s_options
{

} 			t_options;

typedef struct s_philosopher {

} t_philosopher;

typedef struct s_all
{
	pthread_t tread_philosofer;
	pthread_mutex_t **forks;
	pthread_mutex_t *fix_get_time;
	pthread_mutex_t *waiter;
	uint64_t 	*i;
	unsigned 	id_philo;
	unsigned	left_fork;
	unsigned	right_fork;
	unsigned	death;
	unsigned	philo_nbr;
	unsigned 	time_to_die;
	unsigned 	time_to_eat;
	unsigned 	time_to_sleep;
	unsigned 	eat_nbr;
	uint64_t	*last_meal;
	uint64_t	start_time;
}			t_all;


#endif