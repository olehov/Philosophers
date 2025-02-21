/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:23:47 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/21 16:54:27 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <signal.h>

void	*wait_is_full(void	*value)
{
	size_t	i;
	t_table	*table;

	table = (t_table *)value;
	i = 0;
	while (i < table->number_of_philos)
	{
		sem_wait(table->semaphores->is_all_full);
		i++;
	}
	sem_post(table->semaphores->is_finished);
	return (NULL);
}

void	start_controler(t_table	*table)
{
	pthread_create(&table->id, NULL, wait_is_full, table);
}
