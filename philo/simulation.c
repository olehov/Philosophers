/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:45:33 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/11 12:23:15 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->mutexes.set_get_bool, &table->is_end_simulation));
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->mutexes.set_get_bool, &table->ready_to_start))
		;
}

void	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_create(&table->philosophers[i].thread_id, NULL,
			run_thread, &table->philosophers[i]);
		i++;
	}
	pthread_create(&table->table_controller, NULL, ft_table_controller, table);
	set_bool(&table->mutexes.set_get_bool, &table->ready_to_start, true);
	set_long(&table->mutexes.set_get_long,
		&table->start_time, get_time(_MILLISECOND));
	i = 0;
	while (i < table->number_of_philo)
	{
		pthread_detach(table->philosophers[i].thread_id);
		i++;
	}
	pthread_join(table->table_controller, NULL);
}
