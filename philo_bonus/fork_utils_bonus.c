/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:38:15 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/17 17:25:14 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_a_fork(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_message(_TAKE_FORK, get_time(_MILLISECOND),
		philo->id, philo->table);
}

void	take_forks(t_philo *philo)
{
	take_a_fork(philo);
	take_a_fork(philo);
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}
