/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:10:47 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/21 13:10:09 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	print(char *message, size_t time, size_t philo_id, sem_t *sem)
{
	sem_wait(sem);
	printf("%lu %lu %s\n", time, philo_id, message);
	sem_post(sem);
}

void	print_message(t_message type, size_t time,
	size_t philo_id, t_table *table)
{
	if (get_bool(&table->can_print, table->semaphores->can_print)
		|| type == _DIED)
	{
		if (type == _TAKE_FORK)
			print("has taken a fork", time, philo_id, table->semaphores->print);
		else if (type == _EATING)
			print("is eating", time, philo_id, table->semaphores->print);
		else if (type == _SLEEPING)
			print("is sleeping", time, philo_id, table->semaphores->print);
		else if (type == _THINKING)
			print("is thinking", time, philo_id, table->semaphores->print);
		else if (type == _DIED)
			print("died", time, philo_id, table->semaphores->print);
	}
}
