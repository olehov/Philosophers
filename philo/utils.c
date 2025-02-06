/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:38:15 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/06 17:39:11 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_a_fork(t_philo *philo, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	print_message(_TAKE_FORK, get_time(_MILLISECOND),
		philo->id, philo->table);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		take_a_fork(philo, &philo->rigth_fork->fork);
		take_a_fork(philo, &philo->left_fork->fork);
	}
	else
	{
		take_a_fork(philo, &philo->left_fork->fork);
		take_a_fork(philo, &philo->rigth_fork->fork);
	}
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->rigth_fork->fork);
		pthread_mutex_unlock(&philo->left_fork->fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->left_fork->fork);
		pthread_mutex_unlock(&philo->rigth_fork->fork);
	}
}
