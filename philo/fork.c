/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:28:13 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/11 16:05:26 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_handler(t_philosopher *philo, t_fork *fork, bool take)
{
	if (take)
	{
		pthread_mutex_lock(&fork->mutex);
		set_bool(&fork->mutex_state, &fork->is_taken, true);
		if (fork == philo->l_fork)
			print_message(philo, _TAKE_LEFT_FORK);
		else if (fork == philo->r_fork)
			print_message(philo, _TAKE_RIGHT_FORK);
	}
	else
	{
		pthread_mutex_unlock(&fork->mutex);
		set_bool(&fork->mutex_state, &fork->is_taken, false);
	}
}

static int	fork_take(t_philosopher *philo, t_fork *fork, bool take)
{
	bool	is_taken;

	is_taken = false;
	while (philo->state != _DIED || !is_taken
		|| !simulation_finished(philo->table))
	{
		if (get_time(_MILLISECOND) - philo->last_meal_time
			>= philo->table->time_to_die)
		{
			set_state(&philo->table->mutexes.set_get_state,
				&philo->state, _DIED);
			return (-1);
		}
		if (!get_bool(&fork->mutex_state,
				&fork->is_taken))
		{
			fork_handler(philo, fork, take);
			return (0);
		}
	}
	return (0);
}

int	try_take_fork(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		if (fork_take(philo, philo->l_fork, true) == -1)
			return (-1);
		else if (fork_take(philo, philo->r_fork, true) == -1)
		{
			fork_handler(philo, philo->l_fork, false);
			return (-1);
		}
	}
	else
	{
		if (fork_take(philo, philo->r_fork, true) == -1)
			return (-1);
		else if (fork_take(philo, philo->l_fork, true) == -1)
		{
			fork_handler(philo, philo->r_fork, false);
			return (-1);
		}
	}
	return (0);
}
