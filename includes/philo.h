#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# define DEFAULT	0
# define MSG_FORK	"%lld %d has taken a fork \n"
# define MSG_FORK2	"%lld %d has taken a fork \n"
# define MSG_EAT	"%lld %d is eating \n"
# define MSG_SLEEP	"%lld %d sleeping \n"
# define MSG_THINK	"%lld %d is thinking \n"
# define MSG_DEATH	"%lld %d died\n"
# define MSG_ERR_INIT "philosphers init fail\n"
# define MSG_ERR_ARGS "args fail\n"

typedef struct s_options
{
	int				number_of_philosophers;
	int				nbr_of_times_each_ph_must_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	msg;
}					t_options;

typedef struct s_philosophers
{
	int				id;
	int				fork_left;
	int				fork_right;
	uint64_t		time_to_start;
	uint64_t		time_to_lust_meat;
	pthread_mutex_t	*forks;
	t_options		*options;
	int				finish;
}					t_philosophers;

int				ft_atou(char *s);
uint64_t		ft_get_time(void);
int				print_msg_and_exit(char *s, int ret);
void			ft_fix_usleep(uint64_t msec);
void			*ft_live(t_philosophers *ph);
void			ft_is_dead(t_philosophers **ph);
int				ft_start_simulation(t_philosophers **ph);
int				ft_check_valid_args(char **args);
t_options		*ft_get_options(char **argv);
t_philosophers	**ft_get_philosphers(t_options *options);
int				ft_get_init_philospher(t_philosophers **philosophers, \
pthread_mutex_t *forks);
t_philosophers	**ft_clean(t_options *options, \
t_philosophers **philosophers, pthread_mutex_t *forks, int parameter);
int				ft_abs(int n);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
#endif
