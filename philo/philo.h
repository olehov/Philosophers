/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:41:47 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 15:41:07 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include "ft_color_utils.h"

typedef struct s_table	t_table;

typedef enum e_state
{
	_DIED,
	_SLEEPING,
	_THINKING,
	_EATING,
	_TAKE_LEFT_FORK,
	_TAKE_RIGHT_FORK,
	_PUT_LEFT_FORK,
	_PUT_RIGHT_FORK
}	t_state;

typedef enum e_time_type
{
	_SECOND,
	_MILLISECOND,
	_MICROSECOND
}	t_time_type;

typedef struct s_mutex_struct
{
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	set_get_state;
	pthread_mutex_t	set_get_time;
	pthread_mutex_t	set_get_bool;
	pthread_mutex_t	set_get_long;
	pthread_mutex_t	set_get_int;
	pthread_mutex_t	mutex_state;
}	t_mutex;

typedef struct s_fork
{
	int				id;
	int				philo_id_taken;
	bool			is_taken;
	pthread_mutex_t	mutex_state;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philosopher
{
	int				id;
	int				number_of_meals;
	bool			is_full;
	long			last_meal_time;
	t_state			state;
	t_fork			*l_fork;
	t_fork			*r_fork;
	t_table			*table;
	pthread_t		thread_id;
}	t_philosopher;

/*
time_to_die (in milliseconds):
	If a philosopher didn’t start eating time_to_die
	milliseconds since the beginning of their last meal or the beginning
	of the simulation, they die.
time_to_eat (in milliseconds):
	The time it takes for a philosopher to eat.
	During that time, they will need to hold two forks.
time_to_sleep (in milliseconds):
	The time a philosopher will spend sleeping.
meals_to_finish  (optional argument):
	If all philosophers have eaten at least meals_to_finish times,
	the simulation stops. If not specified, the simulation stops when a
	philosopher dies.
*/
struct s_table
{
	int				number_of_philo;
	int				meals_to_finish;
	bool			is_end_simulation;
	bool			ready_to_start;
	long			start_time;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	t_philosopher	*philosophers;
	pthread_t		table_controller;
	t_fork			*forks;
	t_mutex			mutexes;
};

// void			print(char *str, t_philosopher *philo);

/* Initialization and Simulation */
void			table_init(t_table *table, int argc, char **argv);
void			start_simulation(t_table *table);

/* Time and Sleep Management */
int				precise_usleep(size_t usec);
long			get_time(t_time_type time_type);

/* Utility Functions */
size_t			ft_strlen(char *str);
long			ft_atol(char *str);
int				ft_atoi(const char *str);
void			print_error_with_endl(char *error);
void			*safe_malloc(size_t byte);
bool			simulation_finished(t_table *table);
void			fork_handler(t_philosopher *philo,
					t_fork *fork, bool take);
int				try_take_fork(t_philosopher *philo);

/* Philosopher Actions */
int				eating(t_philosopher *philo);
void			sleeping(t_philosopher *philo);
void			thinking(t_philosopher *philo);
void			*run_thread(void *philosopher);
void			wait_all_threads(t_table *table);

/* Table Controller */
void			*ft_table_controller(void *t);

/* Message Printing */
void			print_message(t_philosopher *philo, t_state state);

/* Getters */
int				get_int(pthread_mutex_t *mutex, int	*value);
long			get_long(pthread_mutex_t *mutex, long	*value);
bool			get_bool(pthread_mutex_t *mutex, bool	*value);
t_state			get_state(pthread_mutex_t *mutex, t_state *value);

/* Setters */
void			set_int(pthread_mutex_t *mutex, int *value_to_set, int value);
void			set_long(pthread_mutex_t *mutex,
					long *value_to_set, long value);
void			set_bool(pthread_mutex_t *mutex,
					bool *value_to_set, bool value);
void			set_state(pthread_mutex_t *mutex, t_state *value_to_set,
					t_state value);

void			table_destroy(t_table *table);
#endif
