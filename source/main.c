# include "../includes/philo_one.h"

void ft_exit_error(char *s)
{
	ft_putstr_fd("Error :",2);
	ft_putstr_fd(s,2);
	ft_putchar_fd('\n',2);
	exit(1);
}

int ft_check_nbr_to_str(char *s)
{
	int i;

	i = 0;
	if ( !s || !ft_strlen(s))
		return (1);
	while (s[i])
		if(ft_isdigit(s[i++]))
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
t_options *ft_check_args(char *argv[])
{
	int i;
	t_options *options;

	i = 1;
	while(argv[i])
		if (ft_check_nbr_to_str(argv[i++]))
			return (0);
	options = malloc(sizeof(t_options));
	ft_bzero(options,sizeof(t_options));
	options->philo_nbr = ft_atoitest(argv[2]);
	options->time_to_die = ft_atoitest(argv[3]);
	options->time_to_eat = ft_atoitest(argv[4]);
	options->time_to_sleep = ft_atoitest(argv[5]);
	options->eat_nbr = ft_atoitest(argv[6]);
	return (options);
}
int main(int argc, char *argv[])
{
	t_options *options;
	if (argc < 7 && argc > 5)
		ft_exit_error("check args");
	options = ft_check_args(argv);
	if (!options)
		ft_exit_error("check args");
    printf("Hello Philo");
    return(0);
}