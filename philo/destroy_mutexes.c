/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mutexes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:39:50 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/13 11:36:01 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_and_destroy(pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
	pthread_mutex_destroy(mutex);
}

void	destroy_mutexes(t_mutexes *mutexes)
{
	if (mutexes == NULL)
		return ;
	if (pthread_mutex_destroy(&mutexes->can_print) == -1)
		unlock_and_destroy(&mutexes->can_print);
	if (pthread_mutex_destroy(&mutexes->is_finished) == -1)
		unlock_and_destroy(&mutexes->is_finished);
	if (pthread_mutex_destroy(&mutexes->print) == -1)
		unlock_and_destroy(&mutexes->print);
	if (pthread_mutex_destroy(&mutexes->start) == -1)
		unlock_and_destroy(&mutexes->start);
	free(mutexes);
}
