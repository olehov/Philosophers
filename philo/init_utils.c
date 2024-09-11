/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:36:34 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/11 16:08:10 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_fork(t_philosopher *philo, t_fork *forks, int philo_id)
{
	int	philo_number;

	philo_number = philo->table->number_of_philo;
	philo->l_fork = &forks[(philo_id + 1) % philo_number];
	philo->r_fork = &forks[philo_id];
}

static t_philosopher	*philosophers_init(t_table *table)
{
	t_philosopher	*philos;
	int				i;

	i = 0;
	if (table == NULL)
		return (NULL);
	philos = safe_malloc(sizeof(t_philosopher) * table->number_of_philo);
	if (philos == NULL)
		return (NULL);
	while (i < table->number_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].is_full = false;
		philos[i].last_meal_time = 0;
		philos[i].number_of_meals = 0;
		philos[i].table = table;
		philos[i].state = _EATING;
		assign_fork(&philos[i], table->forks, i);
		i++;
	}
	return (philos);
}

static t_fork	*forks_init(t_table *table)
{
	t_fork	*forks;
	int		i;

	i = 0;
	if (table == NULL)
		return (NULL);
	forks = safe_malloc(sizeof(t_fork) * table->number_of_philo);
	if (forks == NULL)
		return (NULL);
	while (i < table->number_of_philo)
	{
		forks[i].id = i;
		forks[i].is_taken = false;
		pthread_mutex_init(&forks[i].mutex_state, NULL);
		pthread_mutex_init(&forks[i].mutex, NULL);
		i++;
	}
	return (forks);
}

static void	ft_mutex_init(t_table *table)
{
	pthread_mutex_init(&table->mutexes.print_mutex, NULL);
	pthread_mutex_init(&table->mutexes.set_get_bool, NULL);
	pthread_mutex_init(&table->mutexes.set_get_long, NULL);
	pthread_mutex_init(&table->mutexes.set_get_state, NULL);
	pthread_mutex_init(&table->mutexes.set_get_time, NULL);
	pthread_mutex_init(&table->mutexes.set_get_int, NULL);
}

void	table_init(t_table *table, int argc, char **argv)
{
	if (table == NULL)
		return ;
	if (argc == 6)
		table->meals_to_finish = atoi(argv[5]);
	else
		table->meals_to_finish = -1;
	table->number_of_philo = atoi(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]) * 1000;
	table->time_to_sleep = ft_atol(argv[4]) * 1000;
	table->ready_to_start = false;
	table->is_end_simulation = false;
	table->forks = forks_init(table);
	if (table->forks == NULL)
		return ;
	table->philosophers = philosophers_init(table);
	if (table->philosophers == NULL)
		return (free(table->forks));
	ft_mutex_init(table);
}
