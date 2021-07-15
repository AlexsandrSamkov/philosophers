#include "../includes/philo_one.h"

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
	options->number_of_times_each_philosopher_must_eat = ft_atou(argv[5]);
	if (options->number_of_philosophers <= 0 \
		|| options->time_to_die < 120 \
		|| options->time_to_eat < 60 \
		|| options->time_to_sleep < 60)
		return (0);
	return (options);
}

int	ft_get_init_philospher(t_philosophers **philosophers, \
pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < philosophers[0]->options->number_of_philosophers)
	{
		philosophers[i]->count = 0;
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
		return (0);
	forks =\
	malloc(options->number_of_philosophers * sizeof(pthread_mutex_t));
	if (!forks)
		return (0);
	while (i < options->number_of_philosophers)
	{
		philosophers[i] = malloc(sizeof(t_philosophers));
		philosophers[i]->options = options;
		pthread_mutex_init(&forks[i], 0);
		i++;
	}
	ft_get_init_philospher(philosophers, forks);
	return (philosophers);
}
