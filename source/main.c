# include "../includes/philo_one.h"

int g_nbr;
int g_fork_left;
int g_fork_right;
void ft_exit_error(char *s)
{
	ft_putstr_fd("Error :",2);
	ft_putstr_fd(s,2);
	ft_putchar_fd('\n',2);
	exit(1);
}

int ft_check_nbr_to_str(char *s)
{
	int i;

	i = 0;
	if ( !s || !ft_strlen(s))
		return (1);
	while (s[i])
		if(!ft_isdigit(s[i++]))
			return (1);
	return (0);
}
int ft_atoitest(char *s)
{
	int i;
	long long nbr;

	i = 0;
	nbr = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		nbr *= 10;
		nbr += (int)(s[i]) - 48;
		i++;
	}
	return ((int)nbr);
}

void *ft_live(t_options *options)
{
	int nbr = g_nbr;
	int fork_right;
	int fork_left;
	g_nbr++;
	while (1)
	{
		pthread_mutex_lock(&options->forks_left[g_fork_left]);
		fork_left = g_fork_left;
		if (g_fork_left > 2)
			g_fork_left = 0;
		else
			g_fork_left++;
		pthread_mutex_lock(&options->forks_right[g_fork_right]);
		fork_right = g_fork_right;
		if (g_fork_right > 2)
			g_fork_right = 0;
		else
			g_fork_right++;
		printf("eat %d, fork = %d %d\n", nbr, fork_left, fork_right);
		usleep(options->time_to_eat);
		printf("sleep %d, fork = %d %d\n", nbr, fork_left, fork_right);
		usleep(options->time_to_sleep);
		pthread_mutex_unlock(&options->forks_left[fork_left]);
		pthread_mutex_unlock(&options->forks_right[fork_right]);
	}
	return (0);
}

void *ft_death(pthread_mutex_t *death)
{
	pthread_mutex_lock(death);
	return (0);
}
void ft_init_philo(t_options *options)
{
	pthread_t *philo;
	pthread_mutex_t death;
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
	int i;
	g_fork_right = 0;
	g_fork_left = 0;
	g_nbr = 0;

	fork_left = ft_calloc(3,sizeof(pthread_mutex_t));
	if (!fork_left)
		ft_exit_error("fail malloc");
	fork_right = ft_calloc(3,sizeof(pthread_mutex_t));
	if (!fork_right)
		ft_exit_error("fail malloc");


	pthread_mutex_init(&death,0);
	pthread_mutex_lock(&death);
	i = 0;
	while (i < options->philo_nbr)
		pthread_mutex_init(&fork_left[i++],0);
	i = 0;
	while (i < options->philo_nbr)
		pthread_mutex_init(&fork_right[i++],0);
	options->forks_right = fork_right;
	options->forks_left = fork_left;
	i = 0;
	philo = ft_calloc(options->philo_nbr + 1,sizeof (pthread_t));
	if (!philo)
		ft_exit_error("fail malloc");
	while (i < options->philo_nbr)
	{
		if (pthread_create(&philo[i++], 0, (void *) ft_live, options))
			ft_exit_error("pthread_create fail");
		usleep(20);
	}
	sleep(10);

}

t_options *ft_check_args(char *argv[])
{
	int i;
	t_options *options;

	i = 1;
	while(argv[i])
		if (ft_check_nbr_to_str(argv[i++]))
			return (0);
	options = malloc(sizeof(t_options));
	ft_bzero(options,sizeof(t_options));
	options->philo_nbr = ft_atoitest(argv[1]);
	options->time_to_die = ft_atoitest(argv[2]);
	options->time_to_eat = ft_atoitest(argv[3]);
	options->time_to_sleep = ft_atoitest(argv[4]);
	options->eat_nbr = ft_atoitest(argv[5]);
	return (options);
}
int main(int argc, char *argv[])
{
	t_options *options;
	if (argc < 5 || argc > 7)
		ft_exit_error("check args");
	options = ft_check_args(argv);
	if (!options)
		ft_exit_error("check args");
	ft_init_philo(options);
    return(0);
}