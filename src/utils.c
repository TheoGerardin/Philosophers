#include "../includes/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	ft_usleep(int time_in_ms)
{
	long long	start;

	start = get_time();
	while (get_time() - start < time_in_ms)
		usleep(100);
}

void	print_action(t_philosopher *philo, char *action)
{
	pthread_mutex_lock(&philo->params->print_lock);
	printf("%lld %d %s\n", get_time() - philo->params->start_time, philo->id,
		action);
	pthread_mutex_unlock(&philo->params->print_lock);
}
