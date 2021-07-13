# include "../includes/philo_one.h"



uint64_t					ft_get_time(void)
{
	uint64_t				to_return;
	static struct timeval	time;

	gettimeofday(&time, NULL);

	to_return = time.tv_sec * 1000 + time.tv_usec/1000;
	return (to_return);
}

void						ft_fix_usleep(uint64_t msec)
{
	uint64_t				start;
	start = ft_get_time();
	while (ft_get_time() - start < msec)
		usleep(50);
}

int ft_check_valid_args(char **args)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (args[i])
	{
		while (args[i][j])
			if(!ft_strlen(args[i]) || !ft_isdigit(args[i][j]))
				return (1);
		i++;
		j = 0;
	}
	return (0);
}

int ft_atoitest(char *s)
{
	int i;
	long long nbr;

	i = 0;
	nbr = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		nbr *= 10;
		nbr += (int)(s[i]) - 48;
		i++;
	}
	return ((int)nbr);
}


int ft_free(void **p, int ret)
{
	free(*p);
	*p = NULL;
	return(ret);
}
int print_msg_and_exit(char *s, int ret)
{
	ft_putstr_fd(s,2);
	return(ret);
}
options_t *ft_get_options(char ** argv)
{
	options_t *options;

	// if(ft_check_valid_args(argv))
	// 	return (0);
	options = malloc(sizeof(options_t));
	if (!options)
		return (0);
	options->number_of_philosophers = ft_atoitest(argv[1]);
	options->time_to_die = ft_atoitest(argv[2]);
	options->time_to_eat = ft_atoitest(argv[3]);
	options->time_to_sleep = ft_atoitest(argv[4]);
	options->number_of_times_each_philosopher_must_eat = ft_atoitest(argv[5]);
	// if(options->number_of_philosophers <= 0  || options->number_of_philosophers > 200
	// || options->time_to_die < 120 || options->time_to_eat < 60  || options->time_to_sleep < 60)
	// 	return(ft_free(&options, 0));

	return(options);
}

philosophers_t **ft_get_philosphers(options_t *options)
{
	philosophers_t **philosophers;
	pthread_mutex_t *forks;
	int i;

	philosophers = malloc(options->number_of_philosophers * sizeof(philosophers_t *));
	if (!philosophers)
		return (0);
	forks = malloc(options->number_of_philosophers * sizeof(pthread_mutex_t));
	// if (forks)
	// 	return((philosophers_t **)ft_free(&philosophers, 0));
	i = 0;
	while (i < options->number_of_philosophers)
	{
		philosophers[i] = malloc(sizeof(philosophers_t));
		pthread_mutex_init(&forks[i],0);
		i++;
	}
	i = 0;
	while (i < options->number_of_philosophers)
	{
		if (i != options->number_of_philosophers - 1)
		{
			philosophers[i]->fork_left = i;
			philosophers[i]->fork_right = i + 1;
		}
		else
		{
			philosophers[i]->fork_left = i;
			philosophers[i]->fork_right = 0;
		}
		philosophers[i]->id = i + 1;
		philosophers[i]->forks = forks;
		philosophers[i]->options = options;

		philosophers[i]->fork1 = malloc(sizeof(uint64_t));
		philosophers[i]->fork2 = malloc(sizeof(uint64_t));
		philosophers[i]->eat = malloc(sizeof(uint64_t));
		philosophers[i]->sleep = malloc(sizeof(uint64_t));
		philosophers[i]->think = malloc(sizeof(uint64_t));
		philosophers[i]->time_to_lust_meat= malloc(sizeof(uint64_t));
		*philosophers[i]->fork1 = 0;
		*philosophers[i]->fork2 =0;
		*philosophers[i]->eat = 0;
		*philosophers[i]->sleep = 0;
		*philosophers[i]->think = 0;
		*philosophers[i]->time_to_lust_meat= 0;
		i++;

	}
	return(philosophers);
}

void ft_print_msg(char *s, uint64_t time_print, int id,uint64_t *time)
{
	printf(s,time_print,id);
	*time = 0;
}

void *ft_msg(philosophers_t *ph)
{
	while (1)
	{
		while (*ph->fork1)
			ft_print_msg(MSG_FORK, *ph->fork1 - ph->time_to_start, ph->id, ph->fork1);
		while (*ph->fork2)			
			ft_print_msg(MSG_FORK2, *ph->fork2 - ph->time_to_start, ph->id, ph->fork2);
		while (*ph->eat)
			ft_print_msg(MSG_EAT, *ph->eat - ph->time_to_start, ph->id, ph->eat);
		while (*ph->sleep)
			ft_print_msg(MSG_SLEEP, *ph->sleep - ph->time_to_start, ph->id, ph->sleep);
		while (*ph->think)
			ft_print_msg(MSG_THINK, *ph->think - ph->time_to_start, ph->id, ph->think);
	}
	return (0);
}
void *ft_live(philosophers_t *philosophers)
{
	int i;
	i = 0;

	pthread_t msg_tread;
	pthread_create(&msg_tread, 0,(void *)ft_msg,philosophers);
	if (philosophers->id % 2 == 0 && philosophers->id != 1)
		ft_fix_usleep(philosophers->options->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philosophers->forks[philosophers->fork_left]);
		*philosophers->fork1 = ft_get_time();
		pthread_mutex_lock(&philosophers->forks[philosophers->fork_right]);
		*philosophers->fork2 = ft_get_time();
		ft_fix_usleep(philosophers->options->time_to_eat);
		*philosophers->eat = ft_get_time();
		pthread_mutex_unlock(&philosophers->forks[philosophers->fork_left]);
		pthread_mutex_unlock(&philosophers->forks[philosophers->fork_right]);
		
		*philosophers->time_to_lust_meat = ft_get_time();
		*philosophers->sleep = ft_get_time();
		ft_fix_usleep(philosophers->options->time_to_sleep);
		*philosophers->think = ft_get_time();
		i++;
		if (philosophers->options->number_of_times_each_philosopher_must_eat != -1
			&& (int)philosophers->options->number_of_times_each_philosopher_must_eat == i)
			break;
	}
	return (0);
}

void de(philosophers_t **ph)
{
	int i;
	i = 0;
	while (i < ph[0]->options->number_of_philosophers)
	{
		printf("%u left = %u right = %u\n",ph[i]->id,ph[i]->fork_left,
			   ph[i]->fork_right);
		i++;
	}
}

void ft_start_simulation(philosophers_t **philosophers)
{
	pthread_t *threads;
	uint64_t time_to_start;
	int i;
	
	i = 0;
	threads = malloc(philosophers[0]->options->number_of_philosophers * sizeof(pthread_t));
	de(philosophers);
	time_to_start = ft_get_time();	
	while (i < philosophers[0]->options->number_of_philosophers)
	{
		philosophers[i]->time_to_start = time_to_start;
		*philosophers[i]->time_to_lust_meat = time_to_start;
		pthread_create(&threads[i], 0, (void *) ft_live, philosophers[i]);
		i++;
		usleep(500);
	}

	i = 0;
	while (1)
	{
		if ( ft_get_time() -  *philosophers[i]->time_to_lust_meat > philosophers[i]->options->time_to_die)
		{
			printf("died %d\n",philosophers[i]->id);
			break;
		}
		if ( i == philosophers[0]->options->number_of_philosophers - 1)
			i = 0;
		else
			i++;
		usleep(500);
	}	
	
}

int main(int argc, char *argv[])
{
	options_t *options;
	philosophers_t **philosophers;
	if (argc < 5 || argc > 7)
	{
		printf("many args");
		return (1);
	}
	options = ft_get_options(argv);
	if (!options)
		return(print_msg_and_exit("args fail",1));
	philosophers = ft_get_philosphers(options);
	if (!philosophers)
		return(print_msg_and_exit("philosphers init fail",1));
	ft_start_simulation(philosophers);
    return (0);
}
