#include "../includes/philo.h"

void	handle_philosopher_death(t_philosopher *philosopher, t_params *params)
{
	print_action(philosopher, "died");
	pthread_mutex_lock(&params->someone_died_lock);
	params->someone_died = 1;
	pthread_mutex_unlock(&params->someone_died_lock);
	pthread_mutex_lock(&params->stop_lock);
	params->simulation_stop = 1;
	pthread_mutex_unlock(&params->stop_lock);
}

int	check_philosophers(t_philosopher *philosophers, t_params *params,
		int *all_ate)
{
	int			i;
	long long	time_since_last_meal;
	int			times_eaten;

	i = 0;
	while (i < params->num_philosophers)
	{
		pthread_mutex_lock(&params->meals_lock);
		time_since_last_meal = get_time() - philosophers[i].last_meal_time;
		times_eaten = philosophers[i].times_eaten;
		pthread_mutex_unlock(&params->meals_lock);
		if (time_since_last_meal > params->time_to_die)
		{
			handle_philosopher_death(&philosophers[i], params);
			return (1);
		}
		if (params->num_meals != -1 && times_eaten < params->num_meals)
			*all_ate = 0;
		i++;
	}
	return (0);
}

int	monitor_philosophers(t_philosopher *philosophers, t_params *params)
{
	int	all_ate;

	while (1)
	{
		pthread_mutex_lock(&params->death_lock);
		all_ate = 1;
		if (check_philosophers(philosophers, params, &all_ate))
		{
			pthread_mutex_unlock(&params->death_lock);
			return (1);
		}
		if (params->num_meals != -1 && all_ate)
		{
			pthread_mutex_lock(&params->stop_lock);
			params->simulation_stop = 1;
			pthread_mutex_unlock(&params->stop_lock);
			pthread_mutex_unlock(&params->death_lock);
			return (1);
		}
		pthread_mutex_unlock(&params->death_lock);
		usleep(1000);
	}
	return (0);
}

int	check_stop(t_philosopher *philo)
{
	int	should_stop;

	pthread_mutex_lock(&philo->params->stop_lock);
	should_stop = philo->params->simulation_stop;
	pthread_mutex_unlock(&philo->params->stop_lock);
	return (should_stop);
}
