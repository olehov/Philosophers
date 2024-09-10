/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:14:39 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 15:43:45 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *str, t_philosopher *philo)
{
	long	time;

	pthread_mutex_lock(&philo->table->mutexes.print_mutex);
	time = get_time(_MILLISECOND);
	printf("%ld %i %s", time, philo->id, str);
	pthread_mutex_unlock(&philo->table->mutexes.print_mutex);
}

void	print_message(t_philosopher *philo, t_state state)
{
	if (state == _TAKE_LEFT_FORK || state == _TAKE_RIGHT_FORK)
		print("has taken a fork\n", philo);
	else if (state == _EATING && !simulation_finished(philo->table))
		print("is eating\n", philo);
	else if (state == _SLEEPING && !simulation_finished(philo->table))
		print("is sleeping\n", philo);
	else if (state == _THINKING && !simulation_finished(philo->table))
		print("is thinking\n", philo);
	else if (state == _DIED)
		print("died\n", philo);
	else
		return ;
}
