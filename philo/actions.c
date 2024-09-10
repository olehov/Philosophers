/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:14:39 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 15:28:42 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
