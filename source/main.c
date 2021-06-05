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

uint64_t					get_time(void)
{
	uint64_t				to_return;
	static struct timeval	time;

	if (gettimeofday(&time, NULL))
		ft_exit_error(MSG_ERR_TIME);
	to_return = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (to_return);
}

void						fix_usleep(uint64_t msec)
{
	uint64_t				start;

	start = get_time();
	while (get_time() - start < msec)
		usleep(500);
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


t_all **ft_memory_allocation(unsigned len)
{
	t_all **all;
	pthread_mutex_t **forks;
	int i;

	forks = malloc(sizeof(pthread_mutex_t *) * (len + 1));
	if (!forks)
		ft_exit_error(MSG_ERR_MALLOC);
	i = 0;
	while (i < (int)len)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t) * (len + 1));
		i++;
	}
	forks[i] = 0;
	all = malloc((len + 1) * sizeof(t_all *));
	if (!all)
		ft_exit_error(MSG_ERR_MALLOC);
	i = 0;
	while (i < (int)len)
	{
		all[i] = malloc(sizeof (t_all));
		if (!all)
			ft_exit_error(MSG_ERR_MALLOC);
		all[i]->forks = forks;
		i++;
	}
	all[i] = NULL;
	return (all);
}

void *ft_live(t_all *all)
{
	pthread_mutex_lock(all->forks[all->left_fork]);
	return (0);
}

void *ft_start_simulation(t_all **all)
{
	int i;

	i = 0;
	while (all[i])
	{
		pthread_create(&all[i]->tread_philosofer,0,(void *)ft_live,all[i]); //Ошибочка ?
		i++;
	}
	return (0);
}

void ft_init(t_all **all)
{
	int i;
	pthread_t waiter;

	i = 0;
	while (all[i])
	{
		all[i]->left_fork = i;
		pthread_mutex_init(all[i]->forks[i], 0);
		if (i == (int)all[i]->philo_nbr - 1)
			all[i]->right_fork = 0;
		else
			all[i]->right_fork = + 1;//поломалась?

		i++;
	}
	pthread_create(&waiter,0,(void *) ft_start_simulation,(all)); //поломалась?
}

t_all **ft_check_args(char *argv[])
{
	int i;
	t_all **all;
	int len;
	i = 1;
	while(argv[i])
		if (ft_check_nbr_to_str(argv[i++]))
			return (0); // УТЕЧКА
	len = ft_atoitest(argv[1]);
	all = ft_memory_allocation(len);
	i = 0;
	while (all[i])
	{
		all[i]->philo_nbr = ft_atoitest(argv[1]);
		all[i]->time_to_die = ft_atoitest(argv[2]);
		all[i]->time_to_eat = ft_atoitest(argv[3]);
		all[i]->time_to_sleep = ft_atoitest(argv[4]);
		all[i]->eat_nbr = ft_atoitest(argv[5]);
		i++;
	}
	return (all);
}
int main(int argc, char *argv[])
{
	t_all **all;
	if (argc < 5 || argc > 7)
		ft_exit_error("check args");
	all = ft_check_args(argv);
	if (!all)
		ft_exit_error("check args");
	ft_init(all);
    return(0);
}