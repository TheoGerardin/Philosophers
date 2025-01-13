#include "../includes/philo.h"

void	set_params_values(t_params *params, int argc, char **argv)
{
	params->num_philosophers = atoi(argv[1]);
	params->time_to_die = atoi(argv[2]);
	params->time_to_eat = atoi(argv[3]);
	params->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		params->num_meals = atoi(argv[5]);
	else
		params->num_meals = -1;
	params->simulation_stop = 0;
	params->someone_died = 0;
	params->start_time = get_time();
}

int	init_forks(t_params *params)
{
	int	i;

	params->forks = malloc(sizeof(pthread_mutex_t) * params->num_philosophers);
	if (!params->forks)
		return (1);
	i = 0;
	while (i < params->num_philosophers)
	{
		if (pthread_mutex_init(&params->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_locks(t_params *params)
{
	if (pthread_mutex_init(&params->print_lock, NULL) != 0
		|| pthread_mutex_init(&params->death_lock, NULL) != 0
		|| pthread_mutex_init(&params->meals_lock, NULL) != 0
		|| pthread_mutex_init(&params->stop_lock, NULL) != 0
		|| pthread_mutex_init(&params->someone_died_lock, NULL) != 0)
		return (1);
	return (0);
}

int	init_params(t_params *params, int argc, char **argv)
{
	set_params_values(params, argc, argv);
	if (init_forks(params) != 0)
		return (1);
	if (init_locks(params) != 0)
		return (1);
	return (0);
}

void	init_philosophers(t_philosopher *philosophers, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->num_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].times_eaten = 0;
		philosophers[i].last_meal_time = params->start_time;
		philosophers[i].params = params;
		philosophers[i].left_fork = &params->forks[i];
		philosophers[i].right_fork = &params->forks[(i + 1)
			% params->num_philosophers];
		i++;
	}
}
