#include "../includes/philo.h"

void	too_many_lines(pthread_mutex_t *first_fork,
					pthread_mutex_t *second_fork)
{
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}
