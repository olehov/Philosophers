/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthreads_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:53:33 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/07 13:36:23 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philos(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		if (table->philosophers[i] == NULL)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_pthreads_init(t_table *table)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	if (check_philos(table) == -1)
		return (-1);
	while (i < table->number_of_philos)
	{
		philo = (t_philo *)table->philosophers[i];
		pthread_create(&philo->thread_id, NULL,
			start_simulation, philo);
		i++;
	}
	return (0);
}

void	wait_all_threads(t_table *table)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	while (i < table->number_of_philos)
	{
		philo = (t_philo *)table->philosophers[i];
		pthread_join(philo->thread_id, NULL);
		i++;
	}
}
