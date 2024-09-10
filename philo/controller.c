/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:14:39 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 15:58:44 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_full_philosophers(t_table *table)
{
	int	i;
	int	full_philosophers;

	i = -1;
	full_philosophers = 0;
	while (++i < table->number_of_philo)
	{
		if (get_bool(&table->mutexes.set_get_bool,
				&table->philosophers[i].is_full))
			full_philosophers++;
		if (get_state(&table->mutexes.set_get_state,
				&table->philosophers[i].state) == _DIED)
		{
			print_message(&table->philosophers[i], _DIED);
			set_bool(&table->mutexes.set_get_bool,
				&table->is_end_simulation, true);
			break ;
		}
	}
	return (full_philosophers);
}

void	*ft_table_controller(void *t)
{
	t_table		*table;
	int			full_philosophers;

	table = (t_table *)t;
	full_philosophers = 0;
	while (!simulation_finished(table))
	{
		full_philosophers = check_full_philosophers(table);
		if (full_philosophers == table->number_of_philo)
			set_bool(&table->mutexes.set_get_bool,
				&table->is_end_simulation, true);
	}
	return (NULL);
}
