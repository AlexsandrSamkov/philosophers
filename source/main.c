#include "../includes/philo.h"

int	ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

int	main(int argc, char *argv[])
{
	t_philosophers	**philosophers;
	t_options		*options;

	if (argc < 5 || argc > 7)
	{
		printf("many args");
		return (1);
	}
	options = ft_get_options(argv);
	if (!options)
		return (print_msg_and_exit(MSG_ERR_ARGS, 1));
	philosophers = ft_get_philosphers(options);
	if (!philosophers)
		return (print_msg_and_exit(MSG_ERR_INIT, 1));
	if (!ft_start_simulation(philosophers))
		return (print_msg_and_exit(MSG_ERR_INIT, 1));
	ft_clean(options, philosophers, \
	philosophers[0]->forks, options->number_of_philosophers);
	return (0);
}
