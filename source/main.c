# include "../includes/philo_one.h"



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


philosophers_t **ft_init(char **argv)
{
	
}


int main(int argc, char *argv[])
{
	philosophers_t **ph;
	if (argc < 5 || argc > 7)
	{
		printf("many args");
		return (1);
	}
	ph = ft_init(argv);
	ft_start_simulation(ph);
    return(0);
}



// int main(void)
// {
// 	pthread_mutex_t mutex[2];
// 	pthread_t threads;
	
// }