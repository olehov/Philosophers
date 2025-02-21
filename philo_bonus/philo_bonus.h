/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:21:06 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/21 16:52:34 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include "ft_semaphore_bonus.h"
# include "utils_bonus.h"

# define RED     "\x1b[31m"
# define RESET   "\x1b[0m"

typedef struct s_table	t_table;

typedef enum e_message
{
	_TAKE_FORK,
	_EATING,
	_SLEEPING,
	_THINKING,
	_DIED
}	t_message;

typedef struct s_philo
{
	size_t			id;
	size_t			last_meal_time;
	size_t			max_meals;
	size_t			meals_counter;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	bool			is_finish;
	t_table			*table;
	t_named_sem		*m_last_meal_time;
	t_named_sem		*is_finished;
	pthread_t		meal_time_check_id;
	pthread_t		finish_checker_id;
}	t_philo;

/**
 * @struct s_table
 * @param philosophers array of pointers to t_philo struct
 * @param max_meals (optional argument): how many times each philosopher
 * will eat before the simulation stop
 * @param number_of_philos how many philosophers at the table
 * @param time_to_die (in milliseconds): if philosopher didn't start eating
 * time_to_die since the beginning of their last meal
 * or the beginning of simulation, they die
 * @param time_to_eat (in milliseconds): the time it takes for a philosopher
 * to eat. During that time, they will need to hold two forks
 * @param time_to_sleep (in milliseconds):
 * the time a philosopher will spend sleep
 */
typedef struct s_table
{
	t_philo		**philosophers;
	size_t		number_of_philos;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		max_meals;
	bool		can_print;
	t_semapores	*semaphores;
	sem_t		*forks;
	pid_t		*pids;
	pthread_t	id;
}	t_table;

t_philo		*philo_init(size_t id, size_t max_meals, t_table *table);

t_table		*table_init(char *argv[], int argc);

int			ft_pthreads_init(t_table *table);

void		print_message(t_message type, size_t time,
				size_t philo_id, t_table *table);

void		set_bool(bool *var, sem_t *sem, bool value);
void		set_size_t(size_t *var, sem_t *sem, size_t value);

void		start_controler(t_table	*table);
void		start_simulation(t_table *table, size_t philo_id);
void		philo_loop(t_philo	*philo);

bool		get_bool(bool *var, sem_t *sem);
size_t		get_size_t(size_t *var, sem_t *sem);

void		kill_pids(t_table *table);

void		take_forks(t_philo *philo);
void		drop_forks(t_philo *philo);

void		free_philo(t_philo *philo);
void		free_philos(t_philo **philos);
void		free_table(t_table *table);

#endif