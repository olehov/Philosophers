/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:21:20 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/13 11:39:01 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdbool.h>

static void	wait_start_sim(t_table	*table)
{
	while (1)
	{
		if (get_bool(&table->ready_to_start, &table->mutexes->start))
			return ;
	}
}

void	take_a_fork(t_philo *philo, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	print_message(_TAKE_FORK, get_time(_MILLISECOND),
		philo->id, philo->table);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		take_a_fork(philo, &philo->rigth_fork->fork);
		take_a_fork(philo, &philo->left_fork->fork);
	}
	else
	{
		take_a_fork(philo, &philo->left_fork->fork);
		take_a_fork(philo, &philo->rigth_fork->fork);
	}
}

void	eating(t_philo *philo)
{
	size_t	last_meal_time;

	take_forks(philo);
	last_meal_time = get_time(_MILLISECOND);
	set_size_t(&philo->last_meal_time,
		&philo->m_last_meal_time, get_time(_MILLISECOND));
	print_message(_EATING, last_meal_time, philo->id, philo->table);
	precise_usleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->rigth_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
	philo->meals_counter++;
	if (philo->meals_counter == philo->max_meals)
		set_bool(&philo->is_full, &philo->m_is_full, true);
}

void	*start_simulation(void *value)
{
	t_philo	*philo;

	philo = (t_philo *)value;
	wait_start_sim(philo->table);
	set_size_t(&philo->last_meal_time, &philo->m_last_meal_time,
		get_time(_MILLISECOND));
	if (philo->table->number_of_philos == 1)
	{
		print_message(_TAKE_FORK, get_time(_MILLISECOND),
			philo->id, philo->table);
		return (NULL);
	}
	while (!get_bool(&philo->table->is_finished,
			&philo->table->mutexes->is_finished))
	{
		eating(philo);
		print_message(_SLEEPING, get_time(_MILLISECOND),
			philo->id, philo->table);
		precise_usleep(philo->time_to_sleep);
		print_message(_THINKING, get_time(_MILLISECOND),
			philo->id, philo->table);
		precise_usleep(1);
	}
	return (NULL);
}
