#include "../includes/philo.h"

void	*philosopher_life(void *arg)
{
	t_philosopher	*philo;
	int				should_stop;

	philo = (t_philosopher *)arg;
	should_stop = 0;
	while (!should_stop)
	{
		pthread_mutex_lock(&philo->params->stop_lock);
		should_stop = philo->params->simulation_stop;
		pthread_mutex_unlock(&philo->params->stop_lock);
		if (should_stop)
			break ;
		if (!take_forks(philo))
			break ;
		if (!eat(philo))
			break ;
		if (!sleep_and_think(philo))
			break ;
	}
	return (NULL);
}

int	take_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	pthread_mutex_lock(first_fork);
	if (check_stop(philo))
	{
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	if (check_stop(philo))
	{
		too_many_lines(first_fork, second_fork);
		return (0);
	}
	print_action(philo, "has taken fork");
	return (1);
}

int	eat(t_philosopher *philo)
{
	if (check_stop(philo))
		return (0);
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->params->meals_lock);
	philo->last_meal_time = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->params->meals_lock);
	ft_usleep(philo->params->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

int	sleep_and_think(t_philosopher *philo)
{
	if (check_stop(philo))
		return (0);
	print_action(philo, "is sleeping");
	ft_usleep(philo->params->time_to_sleep);
	if (check_stop(philo))
		return (0);
	print_action(philo, "is thinking");
	return (1);
}

void	*single_philosopher_life(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(philo->left_fork);
	print_action(philo, "has taken a fork");
	ft_usleep(philo->params->time_to_die);
	print_action(philo, "died");
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
