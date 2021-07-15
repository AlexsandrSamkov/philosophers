#include "../includes/philo_one.h"


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
		return (print_msg_and_exit("args fail", 1));
	philosophers = ft_get_philosphers(options);
	if (!philosophers)
		return (print_msg_and_exit("philosphers init fail", 1));
	ft_start_simulation(philosophers);
	return (0);
}
