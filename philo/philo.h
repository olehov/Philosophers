/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 22:21:06 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/11 14:40:05 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <sys/time.h>

# define RED     "\x1b[31m"
# define RESET   "\x1b[0m"

typedef struct s_table	t_table;

typedef enum e_time_type
{
	_SECOND,
	_MILLISECOND,
	_MICROSECOND
}	t_time_type;

typedef enum e_message
{
	_TAKE_FORK,
	_EATING,
	_SLEEPING,
	_THINKING,
	_DIED
}	t_message;

typedef struct s_fork
{
	size_t			id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_mutexes
{
	pthread_mutex_t	is_finished;
	pthread_mutex_t	start;
	pthread_mutex_t	can_print;
	pthread_mutex_t	print;
}	t_mutexes;

typedef struct s_philo
{
	size_t				id;
	size_t				last_meal_time;
	size_t				max_meals;
	size_t				meals_counter;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	bool				is_full;
	t_fork				*left_fork;
	t_fork				*rigth_fork;
	t_table				*table;
	pthread_mutex_t		m_is_full;
	pthread_mutex_t		m_last_meal_time;
	pthread_t			thread_id;
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
	bool		is_finished;
	bool		ready_to_start;
	bool		can_print;
	t_mutexes	*mutexes;
	t_fork		**forks;
}	t_table;

t_philo		**philos_init(size_t max_meals, t_table *table);

t_table		*table_init(char *argv[], int argc);

int			ft_pthreads_init(t_table *table);

int			ft_isdigit(int c);

void		print_message(t_message type, size_t time,
				size_t philo_id, t_table *table);

void		set_bool(bool *var, pthread_mutex_t *mutex, bool value);
void		set_size_t(size_t *var, pthread_mutex_t *mutex, size_t value);

void		start_controler(t_table	*table);
void		*start_simulation(void *philo);

bool		get_bool(bool *var, pthread_mutex_t *mutex);
size_t		get_size_t(size_t *var, pthread_mutex_t *mutex);
size_t		get_time(t_time_type time_type);

size_t		ft_strlen(const char *str);

t_mutexes	*init_mutexes(void);

t_fork		**init_forks(size_t size);

char		*ft_ultoa(size_t numb);
char		**ft_split(char const *s, char c);
size_t		ft_atoul(const char *str);

void		precise_usleep(size_t usec);
void		wait_all_threads(t_table *table);

void		drop_forks(t_philo *philo);
void		take_forks(t_philo *philo);

void		destroy_mutexes(t_mutexes *mutexes);
void		free_philos(t_philo **philos);
void		free_forks(t_fork **forks);
void		free_table(t_table *table);

#endif