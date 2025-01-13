#include "../includes/philo.h"

int	create_philosopher_threads(t_philosopher *philosophers, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->num_philosophers)
	{
		if (pthread_create(&philosophers[i].thread, NULL, philosopher_life,
				&philosophers[i]) != 0)
		{
			perror("Error creating thread");
			params->simulation_stop = 1;
			return (i);
		}
		i++;
	}
	return (-1);
}

void	join_threads(t_philosopher *philosophers, int num_threads)
{
	int	i;

	i = 0;
	while (i < num_threads)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_philosopher *philosophers, t_params *params)
{
	int	failed_thread_index;

	failed_thread_index = create_philosopher_threads(philosophers, params);
	if (failed_thread_index != -1)
	{
		join_threads(philosophers, failed_thread_index);
		return (1);
	}
	if (monitor_philosophers(philosophers, params))
	{
		join_threads(philosophers, params->num_philosophers);
		params->threads_joined = 1;
	}
	return (0);
}

int	start_single_philosopher(t_philosopher *philo)
{
	if (pthread_create(&philo->thread, NULL, single_philosopher_life,
			philo) != 0)
	{
		perror("Error creating thread for single philosopher");
		return (1);
	}
	pthread_join(philo->thread, NULL);
	return (0);
}
