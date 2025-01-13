/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:29:39 by tgerardi          #+#    #+#             */
/*   Updated: 2024/08/12 21:18:16 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_params
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	int				threads_joined;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meals_lock;
	pthread_mutex_t	stop_lock;
	int				simulation_stop;
	int				someone_died;
	pthread_mutex_t	someone_died_lock;
}					t_params;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	int				times_eaten;
	long long		last_meal_time;
	t_params		*params;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					t_philosopher;

//clean
void				cleanup(t_philosopher *philosophers, t_params *params);

//init
void				set_params_values(t_params *params, int argc, char **argv);
int					init_forks(t_params *params);
int					init_locks(t_params *params);
int					init_params(t_params *params, int argc, char **argv);
void				init_philosophers(t_philosopher *philosophers,
						t_params *params);

//lifecycle
void				*philosopher_life(void *arg);
void				too_many_lines(pthread_mutex_t *first_fork,
						pthread_mutex_t *second_fork);
int					take_forks(t_philosopher *philo);
int					eat(t_philosopher *philo);
int					sleep_and_think(t_philosopher *philo);
void				*single_philosopher_life(void *arg);

//main
int					ft_parsing(int argc, char **argv);
int					which_start(t_philosopher *philosophers, t_params *params);

//monitor
int					check_philosophers(t_philosopher *philosophers,
						t_params *params,
						int *all_ate);
int					monitor_philosophers(t_philosopher *philosophers,
						t_params *params);
int					check_stop(t_philosopher *philo);

//start_simu
int					create_philosopher_threads(t_philosopher *philosophers,
						t_params *params);
void				join_threads(t_philosopher *philosophers, int num_threads);
int					start_simulation(t_philosopher *philosophers,
						t_params *params);
int					start_single_philosopher(t_philosopher *philo);

//utils
long long			get_time(void);
void				ft_usleep(int time_in_ms);
void				print_action(t_philosopher *philo, char *action);

#endif