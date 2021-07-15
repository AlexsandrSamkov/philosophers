#include "../includes/philo_one.h"

int	ft_atou(char *s)
{
	int			i;
	long long	nbr;

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

uint64_t	ft_get_time(void)
{
	uint64_t				to_return;
	static struct timeval	time;

	gettimeofday(&time, NULL);
	to_return = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (to_return);
}

int	print_msg_and_exit(char *s, int ret)
{
	ft_putstr_fd(s, 2);
	return (ret);
}

void	ft_fix_usleep(uint64_t msec)
{
	uint64_t	start;

	start = ft_get_time();
	while (ft_get_time() - start < msec)
		usleep(500);
}

int	ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

t_philosophers	**ft_clean(t_options *options, \
t_philosophers **philosophers, pthread_mutex_t *forks, int parameter)
{
	int	i;

	i = 0;
	while (i < parameter)
		pthread_mutex_destroy(&forks[i++]);
	free(forks);
	free(options);
	i = 0;
	while (i < parameter)
		free(philosophers[i++]);
	free(philosophers);
	return (0);
}
