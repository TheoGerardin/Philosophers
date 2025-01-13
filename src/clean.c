#include "../includes/philo.h"

void	cleanup(t_philosopher *philosophers, t_params *params)
{
	int	i;

	if (!params->threads_joined)
	{
		i = 0;
		while (i < params->num_philosophers)
		{
			pthread_join(philosophers[i].thread, NULL);
			i++;
		}
	}
	i = 0;
	while (i < params->num_philosophers)
	{
		pthread_mutex_destroy(&params->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&params->print_lock);
	pthread_mutex_destroy(&params->death_lock);
	pthread_mutex_destroy(&params->meals_lock);
	pthread_mutex_destroy(&params->stop_lock);
	pthread_mutex_destroy(&params->someone_died_lock);
	free(params->forks);
	free(philosophers);
}
