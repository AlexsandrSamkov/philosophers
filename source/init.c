#include "../includes/philo.h"

int	ft_check_valid_args(char **args)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (args[i])
	{
		while (args[i][j])
			if (!ft_strlen(args[i]) || !ft_isdigit(args[i][j++]))
				return (1);
		i++;
		j = 0;
	}
	return (0);
}

t_options	*ft_get_options(char **argv)
{
	t_options	*options;

	if (ft_check_valid_args(argv))
		return (0);
	options = malloc(sizeof(t_options));
	if (!options)
		return (0);
	options->number_of_philosophers = ft_atou(argv[1]);
	options->time_to_die = ft_atou(argv[2]);
	options->time_to_eat = ft_atou(argv[3]);
	options->time_to_sleep = ft_atou(argv[4]);
	options->nbr_of_times_each_ph_must_eat = ft_atou(argv[5]);
	if (options->number_of_philosophers <= 0 \
		|| options->time_to_die < 10 \
		|| options->time_to_eat < 60 \
		|| options->time_to_sleep < 60
		|| ft_abs(options->time_to_die \
		- options->time_to_eat - options->time_to_sleep) < 10
		|| options->nbr_of_times_each_ph_must_eat == 0)
		return (0);
	if (!options->nbr_of_times_each_ph_must_eat)
		options->nbr_of_times_each_ph_must_eat = -1;
	return (options);
}

void	ft_fix_philosophers(t_philosophers **philosophers)
{
	philosophers[0]->fork_left = 0;
	philosophers[0]->fork_right = 0;
}

int	ft_get_init_philospher(t_philosophers **philosophers, \
pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philosophers[0]->options->number_of_philosophers)
	{
		philosophers[i]->finish = 0;
		if (i != philosophers[0]->options->number_of_philosophers - 1)
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
		i++;
	}
	if (philosophers[0]->options->number_of_philosophers == 1)
		ft_fix_philosophers(philosophers);
	return (1);
}

t_philosophers	**ft_get_philosphers(t_options *options)
{
	t_philosophers	**philosophers;
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	philosophers =\
	malloc(options->number_of_philosophers * sizeof(t_philosophers *));
	if (!philosophers)
		return (ft_clean(options, philosophers, NULL, DEFAULT));
	forks =\
	malloc(options->number_of_philosophers * sizeof(pthread_mutex_t));
	if (!forks)
		return (ft_clean(options, philosophers, NULL, DEFAULT));
	while (i < options->number_of_philosophers)
	{
		philosophers[i] = malloc(sizeof(t_philosophers));
		if (!philosophers[i])
			return (ft_clean(options, philosophers, forks, i));
		philosophers[i]->options = options;
		pthread_mutex_init(&forks[i], 0);
		i++;
	}
	ft_get_init_philospher(philosophers, forks);
	return (philosophers);
}
