#include "../includes/philo_one.h"

void	*ft_live(t_philosophers *ph)
{
	if (ph->id % 2 == 0 && ph->id != 1)
		ft_fix_usleep(ph->options->time_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&ph->forks[ph->fork_left]);
		printf(MSG_FORK, ft_get_time() - ph->time_to_start, ph->id);
		pthread_mutex_lock(&ph->forks[ph->fork_right]);
		printf(MSG_FORK2, ft_get_time() - ph->time_to_start, ph->id);
		printf(MSG_EAT, ft_get_time() - ph->time_to_start, ph->id);
		ft_fix_usleep(ph->options->time_to_eat);
		pthread_mutex_unlock(&ph->forks[ph->fork_left]);
		pthread_mutex_unlock(&ph->forks[ph->fork_right]);
		ph->time_to_lust_meat = ft_get_time();
		printf(MSG_SLEEP, ft_get_time() - ph->time_to_start, ph->id);
		ft_fix_usleep(ph->options->time_to_sleep);
		printf(MSG_THINK, ft_get_time() - ph->time_to_start, ph->id);
		ph->count++;
		if (ph->options->number_of_times_each_philosopher_must_eat != -1
			&& (int)ph->options->number_of_times_each_philosopher_must_eat \
			== ph->count)
			break ;
	}
	return (0);
}

void	ft_is_dead(t_philosophers **ph)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (1)
	{
		if (ph[i]->count \
		== ph[i]->options->number_of_times_each_philosopher_must_eat - 1)
			count++;
		if (count == ph[i]->options->number_of_philosophers &&
		ph[i]->options->number_of_times_each_philosopher_must_eat < 0)
			break ;
		if ((int)(ft_get_time() - ph[i]->time_to_lust_meat) > \
		ph[i]->options->time_to_die)
		{
			printf(MSG_DEATH, ft_get_time() - ph[i]->time_to_start, ph[i]->id);
			break ;
		}
		if (i == ph[0]->options->number_of_philosophers - 1)
			i = 0;
		else
			i++;
		usleep(500);
	}
}

void	ft_clean_treads(pthread_t *threads, int quantity)
{
	int	i;

	i = 0;
	while (i < quantity)
		pthread_detach(threads[i++]);
	free(threads);
}

int	ft_start_simulation(t_philosophers **ph)
{
	pthread_t	*threads;
	uint64_t	time_to_start;
	int			i;

	i = 0;
	threads =\
	malloc(ph[0]->options->number_of_philosophers * sizeof(pthread_t));
	if (!threads)
	{
		ft_clean(ph[0]->options, ph, ph[0]->forks, \
		ph[0]->options->number_of_philosophers);
		return (0);
	}
	time_to_start = ft_get_time();
	while (i < ph[0]->options->number_of_philosophers)
	{
		ph[i]->time_to_start = time_to_start;
		ph[i]->time_to_lust_meat = time_to_start;
		pthread_create(&threads[i], 0, (void *) ft_live, ph[i]);
		i++;
	}
	ft_is_dead(ph);
	ft_clean_treads(threads, ph[0]->options->number_of_philosophers);
	return (1);
}
