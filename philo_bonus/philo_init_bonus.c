/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:49:35 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/21 12:59:16 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_philo(t_philo *philo)
{
	if (philo == NULL)
		return ;
	philo->id = 0;
	philo->is_finish = false;
	philo->max_meals = 0;
	philo->last_meal_time = 0;
	philo->meals_counter = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	if (philo->m_last_meal_time != NULL)
		ft_destroy_named_semaphore(philo->m_last_meal_time);
	if (philo->is_finished != NULL)
		ft_destroy_named_semaphore(philo->is_finished);
	if (philo->table != NULL)
		free_table(philo->table);
	free(philo);
}

t_philo	*philo_init(size_t id, size_t max_meals, t_table *table)
{
	t_philo	*philo;

	if (table == NULL)
		return (NULL);
	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->is_finished = NULL;
	philo->id = id;
	philo->is_finish = false;
	philo->max_meals = max_meals;
	philo->meals_counter = 0;
	philo->table = table;
	philo->last_meal_time = 0;
	philo->time_to_eat = table->time_to_eat;
	philo->time_to_sleep = table->time_to_sleep;
	philo->m_last_meal_time = ft_init_named_semaphore(SEM_LAST_MEAL_TIME_NAME,
			id);
	if (philo->m_last_meal_time == NULL)
		return (free_philo(philo), NULL);
	philo->is_finished = ft_init_named_semaphore(SEM_IS_FINISH_NAME, philo->id);
	if (philo->is_finished == NULL)
		return (free_philo(philo), NULL);
	return (philo);
}
