/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:57:32 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/03 12:47:12 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_int(pthread_mutex_t *mutex, int *value_to_set, int value)
{
	pthread_mutex_lock(mutex);
	*value_to_set = value;
	pthread_mutex_unlock(mutex);
}

void	set_long(pthread_mutex_t *mutex, long *value_to_set, long value)
{
	pthread_mutex_lock(mutex);
	*value_to_set = value;
	pthread_mutex_unlock(mutex);
}

void	set_bool(pthread_mutex_t *mutex, bool *value_to_set, bool value)
{
	pthread_mutex_lock(mutex);
	*value_to_set = value;
	pthread_mutex_unlock(mutex);
}

void	set_state(pthread_mutex_t *mutex, t_state *value_to_set,
			t_state value)
{
	pthread_mutex_lock(mutex);
	*value_to_set = value;
	pthread_mutex_unlock(mutex);
}
