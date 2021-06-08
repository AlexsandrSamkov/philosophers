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

uint64_t					ft_get_time(void)
{
	uint64_t				to_return;
	static struct timeval	time;

	if (gettimeofday(&time, NULL))
		ft_exit_error(MSG_ERR_TIME);
	to_return = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (to_return);
}

void						ft_fix_usleep(uint64_t msec)
{
	uint64_t				start;

	start = ft_get_time();
	while (ft_get_time() - start < msec)
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


void	*ft_calloc_and_check(size_t count, size_t size)
{
	void *p;

	p = ft_calloc(count, size);
	if (!p)
		ft_exit_error(MSG_ERR_MALLOC);
	return (p);
}

philosophers_t **ft_memory_phocation(int len)
{
	philosophers_t **res;
	pthread_mutex_t **forks;
	pthread_mutex_t *waiter;
	int i;

	res = ft_calloc_and_check(len + 1,sizeof(philosophers_t *));
	forks = ft_calloc_and_check(len + 1,sizeof(pthread_mutex_t *));
	waiter = ft_calloc_and_check(1,sizeof(pthread_mutex_t *));
	i = 0;
	while (i < len)
		forks[i++] = ft_calloc_and_check(1,sizeof(pthread_mutex_t));
	i = 0;
	while (i < len)
	{
		res[i] = ft_calloc_and_check(1,sizeof(philosophers_t));
		res[i]->waiter = waiter;
		res[i]->time_to_lust_meal = ft_calloc_and_check(1, sizeof(uint64_t));
		res[i]->forks = forks;
		i++;
	}
	return (res);;

}

uint64_t g_last_meal[4];

void *ft_live(philosophers_t *ph)
{
	int i;
	i = 0;
	while (1)
	{
		if (pthread_mutex_lock(ph->waiter))
			printf(MSG_ERR_MUTEX);
		if (pthread_mutex_lock(ph->forks[ph->fork_left]))
			printf(MSG_ERR_MUTEX);
		printf(MSG_FORK, ft_get_time() - ph->time_to_start, ph->id,
				ph->fork_left);
		if (pthread_mutex_lock(ph->forks[ph->fork_right]))
			printf(MSG_ERR_MUTEX);
		printf(MSG_FORK2, ft_get_time() - ph->time_to_start, ph->id,
			   ph->fork_right);
		if (pthread_mutex_unlock(ph->waiter))
			printf(MSG_ERR_MUTEX);
		//printf(MSG_EAT, ft_get_time() - ph->time_to_start, ph->id);
		ft_fix_usleep(ph->time_to_eat);
		*ph->time_to_lust_meal = ft_get_time();
		if (pthread_mutex_unlock(ph->forks[ph->fork_left]))
			printf(MSG_ERR_MUTEX);
		if (pthread_mutex_unlock(ph->forks[ph->fork_right]))
			printf(MSG_ERR_MUTEX);
		printf(MSG_SLEEP, ft_get_time() - ph->time_to_start, ph->id);
		ft_fix_usleep(ph->time_to_sleep);
		printf(MSG_THINK, ft_get_time() - ph->time_to_start, ph->id);
		i++;
		if (ph->number_of_cycles && (int)ph->number_of_cycles == i)
			break;
	}
	return (0);
}

void ft_start_simulation(philosophers_t **ph)
{
	int i;
	uint64_t time_to_start;
	pthread_t **threads;

	threads = ft_calloc_and_check(ph[0]->nbr_ph + 1, sizeof(pthread_t *));
	i = 0;
	while (i < ph[0]->nbr_ph)
		threads[i++] = ft_calloc_and_check(ph[0]->nbr_ph, sizeof(pthread_t));
	time_to_start = ft_get_time();
	i = 0;
	while (i < ph[0]->nbr_ph)
	{
		if (i % 2 == 0)
		{
			ph[i]->time_to_start = time_to_start;
			ph[i]->time_to_die = time_to_start;
			pthread_create(threads[i], 0, (void *) ft_live, ph[i]);
		}
		i++;
	}
	i = 0;
	while (i < ph[0]->nbr_ph)
	{
		if (i % 2 != 0)
		{
			ph[i]->time_to_start = time_to_start;
			ph[i]->time_to_die = time_to_start;
			pthread_create(threads[i], 0, (void *) ft_live, ph[i]);
		}
		i++;
	}
	i = 0;
	while (1)
	{
		if ( ft_get_time() -  *ph[i]->time_to_lust_meal)
			break;
		if (i == ph[0]->nbr_ph -1 )
			i = 0;
		else
			i++;
		sleep(1);
	}
}


philosophers_t **ft_init(char *argv[])
{
	int i;
	philosophers_t **ph;

	ph = ft_memory_phocation(ft_atoitest(argv[1]));
	i = 0;
	while (ph[i])
	{
		ph[i]->nbr_ph = ft_atoitest(argv[1]);
		ph[i]->time_to_die = ft_atoitest(argv[2]);
		ph[i]->time_to_eat = ft_atoitest(argv[3]);
		ph[i]->time_to_sleep = ft_atoitest(argv[4]);
		ph[i]->number_of_cycles = ft_atoitest(argv[5]);
		ph[i]->id = i + 1;
		ph[i]->fork_left = i;
		if (i == ph[i]->nbr_ph -1)
			ph[i]->fork_right = 0;
		else
			ph[i]->fork_right = i + 1;
		pthread_mutex_init(ph[i]->forks[i],0);
		i++;
	}
	if (pthread_mutex_init(ph[0]->waiter,0))
		ft_exit_error(MSG_ERR_MUTEX);
	return (ph);
}

int main(int argc, char *argv[])
{
	philosophers_t **ph;
	if (argc < 5 || argc > 7)
		ft_exit_error("check args");
	ph = ft_init(argv);
	ft_start_simulation(ph);
    return(0);
}