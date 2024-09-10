/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:14:39 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 15:44:01 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*run_thread(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	wait_all_threads(philo->table);
	philo->last_meal_time = get_time(_MILLISECOND);
	while (!simulation_finished(philo->table))
	{
		if (eating(philo) == -1)
			break ;
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
