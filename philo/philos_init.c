/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 15:49:35 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/13 13:37:01 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*philo_init(size_t id, size_t max_meals, t_table *table)
{
	t_philo	*philo;

	if (table == NULL)
		return (NULL);
	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->id = id;
	philo->is_full = false;
	philo->max_meals = max_meals;
	philo->meals_counter = 0;
	philo->table = table;
	philo->last_meal_time = 0;
	philo->time_to_eat = table->time_to_eat;
	philo->time_to_sleep = table->time_to_sleep;
	if (pthread_mutex_init(&philo->m_is_full, NULL) == -1)
		return (free(philo), NULL);
	if (pthread_mutex_init(&philo->m_last_meal_time, NULL) == -1)
	{
		pthread_mutex_destroy(&philo->m_is_full);
		return (free(philo), NULL);
	}
	return (philo);
}

void	free_philo(t_philo *philo)
{
	if (philo == NULL)
		return ;
	philo->id = 0;
	philo->is_full = false;
	philo->max_meals = 0;
	philo->last_meal_time = 0;
	philo->meals_counter = 0;
	philo->time_to_eat = 0;
	philo->time_to_sleep = 0;
	pthread_mutex_destroy(&philo->m_is_full);
	pthread_mutex_destroy(&philo->m_last_meal_time);
	free(philo);
}

void	free_philos(t_philo **philos)
{
	int	i;

	if (philos == NULL)
		return ;
	i = 0;
	while (philos[i] != NULL)
	{
		free(philos[i]);
		philos[i] = NULL;
		i++;
	}
	free(philos);
	philos = NULL;
}

t_philo	**philos_init(size_t max_meals, t_table *table)
{
	t_philo	**philos;
	size_t	id;

	if (table == NULL)
		return (NULL);
	printf("number of philos: %lu\n", table->number_of_philos);
	printf("malloc philos\n");
	philos = malloc(sizeof(t_philo *) * (table->number_of_philos + 1));
	if (philos == NULL)
		return (NULL);
	id = 0;
	while (id < table->number_of_philos)
	{
		printf("philo_init: id: %lu", id + 1);
		philos[id] = philo_init(id + 1, max_meals, table);
		if (philos[id] == NULL)
		{
			free_philos(philos);
			return (NULL);
		}
		id++;
	}
	philos[id] = NULL;
	return (philos);
}
