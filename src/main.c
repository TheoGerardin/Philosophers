#include "../includes/philo.h"

int	ft_parsing(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep \
        [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	return (0);
}

int	which_start(t_philosopher *philosophers, t_params *params)
{
	if (params->num_philosophers == 1)
		return (start_single_philosopher(&philosophers[0]));
	else
		return (start_simulation(philosophers, params));
}

int	main(int argc, char **argv)
{
	t_params		params;
	t_philosopher	*philosophers;
	int				result;

	if (ft_parsing(argc, argv))
		return (1);
	if (init_params(&params, argc, argv))
		return (1);
	philosophers = malloc(sizeof(t_philosopher) * params.num_philosophers);
	if (!philosophers)
	{
		cleanup(NULL, &params);
		return (1);
	}
	init_philosophers(philosophers, &params);
	result = which_start(philosophers, &params);
	if (result)
	{
		cleanup(philosophers, &params);
		return (1);
	}
	return (0);
}
