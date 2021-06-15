# include "../includes/philo_one.h"

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
	to_return = time.tv_sec * 1000 + time.tv_usec/1000;
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
	unsigned *start;
	int i;

	start = ft_calloc_and_check(1, sizeof(unsigned));
	res = ft_calloc_and_check(len + 1,sizeof(philosophers_t *));
	forks = ft_calloc_and_check(len + 1,sizeof(pthread_mutex_t *));
	waiter = ft_calloc_and_check(1,sizeof(pthread_mutex_t));
	i = 0;
	while (i < len)
	{
		forks[i] = ft_calloc_and_check(1, sizeof(pthread_mutex_t));
		i++;
	}
	i = 0;
	while (i < len)
	{
		res[i] = ft_calloc_and_check(1,sizeof(philosophers_t));
		res[i]->waiter = waiter;
		res[i]->time_to_lust_meal = ft_calloc_and_check(1, sizeof(uint64_t));
		res[i]->forks = forks;
		res[i]->start = start; 
		res[i]->fork1 = ft_calloc_and_check(1, sizeof(uint64_t));
		res[i]->fork2 = ft_calloc_and_check(1, sizeof(uint64_t));
		res[i]->eat = ft_calloc_and_check(1, sizeof(uint64_t));
		res[i]->sleep = ft_calloc_and_check(1, sizeof(uint64_t));
		res[i]->think = ft_calloc_and_check(1, sizeof(uint64_t));
		res[i]->time_to_start = ft_calloc_and_check(1, sizeof(uint64_t));
		i++;
	}
	return (res);

}
void ft_print_msg(char *s, uint64_t time_print, int id,uint64_t *time)
{
	printf(s,time_print,id);
	*time = 0;
}
void ft_msg(philosophers_t *ph)
{
	while (1)
	{
		while (*ph->fork1)
			ft_print_msg(MSG_FORK, *ph->fork1 - *ph->time_to_start, ph->id, ph->fork1);
		while (*ph->fork2)			
			ft_print_msg(MSG_FORK2, *ph->fork2 - *ph->time_to_start, ph->id, ph->fork2);
		while (*ph->eat)
			ft_print_msg(MSG_EAT, *ph->eat - *ph->time_to_start, ph->id, ph->eat);
		while (*ph->sleep)
			ft_print_msg(MSG_SLEEP, *ph->sleep - *ph->time_to_start, ph->id, ph->sleep);
		while (*ph->think)
			ft_print_msg(MSG_THINK, *ph->think - *ph->time_to_start, ph->id, ph->think);
	}
}


void *ft_live(philosophers_t *ph)
{
	int i;
	i = 0;
	pthread_t msg_tread;
	pthread_create(&msg_tread, 0,(void *)ft_msg,ph);
	if ((int)ph->id == ph->nbr_ph)
		*ph->time_to_start = ft_get_time();
	while (*ph->time_to_start == 0);
	*ph->time_to_lust_meal = *ph->time_to_start;
	if (!(ph->id % 2))
		ft_fix_usleep(ph->time_to_eat);
	while (1)
	{
		pthread_mutex_lock(ph->forks[ph->fork_left]);
		*ph->fork1 = ft_get_time();
		pthread_mutex_lock(ph->forks[ph->fork_right]);
		*ph->fork2 = ft_get_time();
		*ph->eat = ft_get_time();
		pthread_mutex_unlock(ph->forks[ph->fork_left]);
		pthread_mutex_unlock(ph->forks[ph->fork_right]);
		ft_fix_usleep(ph->time_to_eat);
		*ph->time_to_lust_meal = ft_get_time();
		*ph->sleep = ft_get_time();
		ft_fix_usleep(ph->time_to_sleep);
		*ph->think = ft_get_time();
		i++;
		if (ph->number_of_cycles && (int)ph->number_of_cycles == i)
			break;
	}
	return (0);
}

void de(philosophers_t **ph)
{
	int i;
	i = 0;
	while (ph[i])
	{
		printf("%u left = %u right = %u\n",ph[i]->id,ph[i]->fork_left,
		 ph[i]->fork_right);
		i++;
	}
}

void ft_start_simulation(philosophers_t **ph)
{
	int i;
	pthread_t **threads;
	threads = ft_calloc_and_check(ph[0]->nbr_ph + 1, sizeof(pthread_t *));
	i = 0;
	ph[0]->start = 0;
	while (i < ph[0]->nbr_ph)
		threads[i++] = ft_calloc_and_check(ph[0]->nbr_ph, sizeof(pthread_t));
	i = 0;
	de(ph);
	while (i < ph[0]->nbr_ph)
	{
		pthread_create(threads[i], 0, (void *) ft_live, ph[i]);
		i++;
	}
	while (!*ph[0]->time_to_start);
	i = 0;
	while (1)
	{
		if ( ft_get_time() -  *ph[i]->time_to_lust_meal > ph[i]->time_to_die)
		{
			printf("died %d\n",ph[i]->id);
			break;
		}
		if ( i == ph[i]->nbr_ph - 1)
			i = 0;
		else
			i++;
		usleep(500);
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
		if (pthread_mutex_init(ph[i]->forks[i], NULL))
			ft_exit_error(MSG_ERR_MUTEX);
		i++;
	}
	if (pthread_mutex_init(ph[0]->waiter, NULL))
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



// int main(void)
// {
// 	uint64_t raz;
// 	uint64_t dva;
// 	int *nbr;
// 	gaga = 1;
// 	nbr = malloc(sizeof(int));
// 	*nbr = 1;
// 	pthread_create(&test, 0,(void *)my_test,(void *)nbr);
// 	raz = ft_get_time();
// 	nbr = 0;
// 	dva = ft_get_time();
// 	printf("%llu",dva - raz);
// 	while (1);
	
// }