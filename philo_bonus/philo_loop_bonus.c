/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:47:28 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/21 16:53:14 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	size_t	last_meal_time;

	take_forks(philo);
	last_meal_time = get_time(_MILLISECOND);
	set_size_t(&philo->last_meal_time,
		philo->m_last_meal_time->sem, get_time(_MILLISECOND));
	print_message(_EATING, last_meal_time, philo->id, philo->table);
	precise_usleep(philo->time_to_eat);
	drop_forks(philo);
	philo->meals_counter++;
	if (philo->meals_counter == philo->max_meals)
		sem_post(philo->table->semaphores->is_all_full);
}

void	sleeping(t_philo *philo)
{
	print_message(_SLEEPING, get_time(_MILLISECOND),
		philo->id, philo->table);
	precise_usleep(philo->time_to_sleep);
}

void	philo_loop(t_philo	*philo)
{
	while (1)
	{
		if (get_bool(&philo->is_finish, philo->is_finished->sem) == true)
			break ;
		eating(philo);
		sleeping(philo);
		print_message(_THINKING, get_time(_MILLISECOND),
			philo->id, philo->table);
	}
}
