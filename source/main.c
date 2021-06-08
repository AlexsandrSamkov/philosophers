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


t_all **ft_memory_allocation(unsigned len)
{
	t_all **all;
	pthread_mutex_t **forks;
	pthread_mutex_t *fix_time;
	pthread_mutex_t *waiter;
	int i;

	fix_time = malloc(sizeof(pthread_mutex_t));
	waiter = malloc(sizeof(pthread_mutex_t));
	forks = malloc(sizeof(pthread_mutex_t *) * (len + 1));
	if (!forks)
		ft_exit_error(MSG_ERR_MALLOC);
	i = 0;
	while (i < (int)len)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
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
		all[i]->i =  malloc(sizeof (uint64_t));

		*(all[i]->i) = 1;
		all[i]->last_meal = malloc(sizeof(uint64_t));	
		all[i]->forks = forks;
		all[i]->waiter = waiter;
		all[i]->fix_get_time = fix_time;
		i++;
	}
	all[i] = NULL;
	return (all);
}

uint64_t g_last_meal[4];

void *ft_live(t_all *all)
{
	int i;
	i = 0;
	while (i++ < 10 )
	{
		pthread_mutex_lock(all->forks[all->left_fork]);
		printf(MSG_FORK,ft_get_time() - all->start_time, all->id_philo );
		pthread_mutex_lock(all->forks[all->right_fork]);
		printf(MSG_FORK2,ft_get_time() - all->start_time, all->id_philo );
		printf(MSG_EAT,ft_get_time() - all->start_time, all->id_philo );
		ft_fix_usleep(all->time_to_eat);
		//usleep(all->time_to_eat * 1000);
		g_last_meal[all->id_philo - 1] = ft_get_time() ;
		*(all->i) += 1;
		//*(all->last_meal) = ft_get_time();
		pthread_mutex_unlock(all->forks[all->left_fork]);
		pthread_mutex_unlock(all->forks[all->right_fork]);
		printf(MSG_SLEEP,ft_get_time() - all->start_time, all->id_philo );
		ft_fix_usleep(all->time_to_sleep);
		//usleep(all->time_to_sleep * 1000);
		printf(MSG_THINK,ft_get_time() - all->start_time, all->id_philo );
	}

	return (0);
}

void *ft_start_simulation(t_all **all)
{
	int i;
	uint64_t start_time;
	int len;
	len = all[0]->philo_nbr % 2;
	i = 0;
	t_all *a0;
	t_all *a1;
	t_all *a2;
	t_all *a3;
	a0 = all[0];
	a1 = all[1];
	a2 = all[2];
	a3 = all[3];
	start_time = ft_get_time();
		all[0]->start_time  = start_time;
		*(all[0]->last_meal) = start_time;
		all[0]->id_philo = 0 + 1;
		pthread_create(&all[0]->tread_philosofer,0,(void *)ft_live,all[0]);
		all[2]->start_time  = start_time;
		*(all[2]->last_meal) = start_time;
		all[2]->id_philo = 2 + 1;
		ft_fix_usleep(all[0]->time_to_eat);
		pthread_create(&all[2]->tread_philosofer,0,(void *)ft_live,all[2]);
		all[1]->start_time  = start_time;
		*(all[1]->last_meal) = start_time;
		all[1]->id_philo = 1 + 1;
		pthread_create(&all[1]->tread_philosofer,0,(void *)ft_live,all[1]);
		all[3]->start_time  = start_time;
		*(all[3]->last_meal) = start_time;
		all[3]->id_philo = 3 + 1;
		pthread_create(&all[3]->tread_philosofer,0,(void *)ft_live,all[3]);
	while ( i <  (int)all[0]->philo_nbr)
	{

		//usleep(1000);
		//Ошибочка ?
		i++;
	}
	uint64_t test;
	test = 0;
	i = 0;
//	while (1)
//	{
//		ft_fix_usleep(all[0]->time_to_die/2);
//		pthread_mutex_lock(all[0]->fix_get_time);
//		test =  g_last_meal[0] - start_time;
//		// if (test > all[i]->time_to_die)
//		// {
//		// 	break;
//		// }
//		pthread_mutex_unlock(all[0]->fix_get_time);
//		if (i >= (int) all[i]->philo_nbr - 1)
//			i = 0;
//		else
//			i++;
//		printf("---------------------%llu\n",test);
//	}
	t_all *a;
	a = all[i];
	sleep(3);
printf("%llu Кто то умер",test);


	return (0);
}

void ft_init(t_all **all)
{
	int i;
	pthread_t waiter;

	i = 0;
	i = 2 % 2;
	pthread_mutex_init(all[0]->fix_get_time, 0);
	while (all[i])
	{
		all[i]->left_fork = i;
		pthread_mutex_init(all[i]->forks[i], 0);
		if (i == (int)all[i]->philo_nbr - 1)
			all[i]->right_fork = 0;
		else
			all[i]->right_fork = i + 1;
		i++;
	}
	pthread_create(&waiter,0,(void *) ft_start_simulation,(all)); //поломалась?
	pthread_join(waiter, 0);
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