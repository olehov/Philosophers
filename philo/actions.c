/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:14:39 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 14:47:00 by ogrativ          ###   ########.fr       */
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
	while (philo->state != _DIED || !is_taken)
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
	bool	is_taken;

	is_taken = false;
	if (philo->id % 2 == 0)
	{
		if (fork_take(philo, philo->l_fork, true) == -1)
			return (-1);
		return (fork_take(philo, philo->r_fork, true));
	}
	else
	{
		if (fork_take(philo, philo->r_fork, true) == -1)
			return (-1);
		return (fork_take(philo, philo->l_fork, true));
	}
	return (0);
}

void	finish_eating(t_philosopher *philo)
{
	fork_handler(philo, philo->l_fork, false);
	fork_handler(philo, philo->r_fork, false);
}

int	eating(t_philosopher *philo)
{
	if (try_take_fork(philo) == -1)
		return (-1);
	print_message(philo, _EATING);
	set_long(&philo->table->mutexes.set_get_long, &philo->last_meal_time,
		get_time(_MILLISECOND));
	precise_usleep(philo->table->time_to_eat);
	philo->number_of_meals++;
	if (philo->table->meals_to_finish > 0
		&& philo->number_of_meals == philo->table->meals_to_finish)
		set_bool(&philo->table->mutexes.set_get_bool, &philo->is_full, true);
	finish_eating(philo);
	return (0);
}

void	sleeping(t_philosopher *philo)
{
	print_message(philo, _SLEEPING);
	if (get_time(_MILLISECOND) - philo->last_meal_time
		> philo->table->time_to_die)
	{
		precise_usleep((get_time(_MILLISECOND) - philo->last_meal_time) * 1000);
		print_message(philo, _DIED);
		set_bool(&philo->table->mutexes.set_get_bool,
			&philo->table->is_end_simulation, true);
		return ;
	}
	precise_usleep(philo->table->time_to_sleep);
}

void	thinking(t_philosopher *philo)
{
	print_message(philo, _THINKING);
	precise_usleep(1000);
}
