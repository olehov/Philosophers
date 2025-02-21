/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:21:20 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/21 17:30:27 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <stdbool.h>

void	*is_finish_checker(void	*value)
{
	t_philo	*philo;

	philo = (t_philo *)value;
	precise_usleep(5);
	if (sem_wait(philo->table->semaphores->is_finished) == 0)
	{
		set_bool(&philo->is_finish, philo->is_finished->sem, true);
		set_bool(&philo->table->can_print,
			philo->table->semaphores->can_print, false);
		sem_post(philo->table->semaphores->is_finished);
		sem_post(philo->table->semaphores->is_all_full);
	}
	return (NULL);
}

void	*last_meal_time_checker(void *value)
{
	t_philo	*philo;
	size_t	last_meal;
	size_t	now;

	philo = (t_philo *)value;
	while (1)
	{
		last_meal = get_size_t(&philo->last_meal_time,
				philo->m_last_meal_time->sem);
		now = get_time(_MILLISECOND);
		if (now - last_meal > philo->table->time_to_die)
		{
			print_message(_DIED, get_time(_MILLISECOND),
				philo->id, philo->table);
			sem_post(philo->table->semaphores->is_finished);
			break ;
		}
		if (get_bool(&philo->is_finish, philo->is_finished->sem) == true)
			break ;
		precise_usleep(1);
	}
	return (NULL);
}

void	start_threads(t_philo *philo)
{
	pthread_t	id;
	pthread_t	finish_checker_id;

	pthread_create(&finish_checker_id, NULL, is_finish_checker, philo);
	pthread_create(&id, NULL, last_meal_time_checker, philo);
}

void	start_simulation(t_table *table, size_t philo_id)
{
	t_philo		*philo;

	philo = philo_init(philo_id, table->max_meals, table);
	if (!philo)
	{
		kill_pids(table);
		exit(EXIT_FAILURE);
	}
	sem_wait(table->semaphores->start);
	sem_post(table->semaphores->start);
	philo->last_meal_time = get_time(_MILLISECOND);
	pthread_create(&philo->finish_checker_id, NULL, is_finish_checker, philo);
	pthread_create(&philo->meal_time_check_id, NULL,
		last_meal_time_checker, philo);
	if (philo->id % 2 == 0)
		precise_usleep(1);
	if (table->number_of_philos == 1)
		print_message(_TAKE_FORK, get_time(_MILLISECOND), philo->id, table);
	else
		philo_loop(philo);
	pthread_join(philo->meal_time_check_id, NULL);
	pthread_join(philo->finish_checker_id, NULL);
	free_philo(philo);
}
