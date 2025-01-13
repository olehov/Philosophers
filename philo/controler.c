/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 18:23:47 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/13 14:09:56 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_died(t_table *table, size_t i)
{
	size_t	current_time;
	size_t	last_meal_time;

	last_meal_time = get_size_t(&table->philosophers[i]->last_meal_time,
			&table->philosophers[i]->m_last_meal_time);
	current_time = get_time(_MILLISECOND);
	if (current_time - last_meal_time >= table->time_to_die)
	{
		set_bool(&table->is_finished, &table->mutexes->is_finished, true);
		set_bool(&table->can_print, &table->mutexes->can_print, false);
		print_message(_DIED, current_time, table->philosophers[i]->id, table);
		return (true);
	}
	return (false);
}

void	start_controler(t_table	*table)
{
	size_t	i;
	size_t	is_full_count;

	i = 0;
	is_full_count = 0;
	set_bool(&table->ready_to_start, &table->mutexes->start, true);
	precise_usleep(1);
	while (true)
	{
		if (i == table->number_of_philos)
		{
			is_full_count = 0;
			i = 0;
		}
		if (is_died(table, i))
			break ;
		if (get_bool(&table->philosophers[i]->is_full,
				&table->philosophers[i]->m_is_full) == true)
			is_full_count++;
		if (is_full_count == table->number_of_philos)
		{
			set_bool(&table->is_finished, &table->mutexes->is_finished, true);
			break ;
		}
		i++;
	}
}
