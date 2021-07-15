#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include "../libs/libft/libft.h"
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# define DEFAULT 0
# define MSG_FORK	"%lld %d has taken a fork \n"
# define MSG_FORK2	"%lld %d has taken a fork \n"
# define MSG_EAT	"%lld %d is eating \n"
# define MSG_SLEEP	"%lld %d sleeping \n"
# define MSG_THINK	"%lld %d is thinking \n"
# define MSG_DEATH "%lld died %d\n"

typedef struct s_options
{
	int				number_of_philosophers;
	int		 		number_of_times_each_philosopher_must_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	pthread_mutex_t	msg;
}	t_options;

typedef struct s_philosophers
{
	int				id;
	unsigned int	fork_left;
	unsigned int	fork_right;
	uint64_t		time_to_start;
	uint64_t		time_to_lust_meat;
	pthread_mutex_t	*forks;
	t_options		*options;
	int 			count;
}					t_philosophers;

int				ft_atou(char *s);
uint64_t		ft_get_time(void);
int				print_msg_and_exit(char *s, int ret);
void			ft_fix_usleep(uint64_t msec);
void			*ft_live(t_philosophers *ph);
void			ft_is_dead(t_philosophers **ph);
int			ft_start_simulation(t_philosophers **ph);
int				ft_check_valid_args(char **args);
t_options		*ft_get_options(char **argv);
t_philosophers	**ft_get_philosphers(t_options *options);
int				ft_get_init_philospher(t_philosophers **philosophers, \
pthread_mutex_t *forks);
t_philosophers	**ft_clean(t_options *options, \
			t_philosophers **philosophers, pthread_mutex_t *forks, int parameter);
#endif