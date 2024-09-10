/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:53:05 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/03 12:45:11 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_int(pthread_mutex_t *mutex, int	*value)
{
	int	tmp;

	pthread_mutex_lock(mutex);
	tmp = *value;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

long	get_long(pthread_mutex_t *mutex, long	*value)
{
	long	tmp;

	pthread_mutex_lock(mutex);
	tmp = *value;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

t_state	get_state(pthread_mutex_t *mutex, t_state *value)
{
	t_state	tmp;

	pthread_mutex_lock(mutex);
	tmp = *value;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

bool	get_bool(pthread_mutex_t *mutex, bool	*value)
{
	bool	tmp;

	pthread_mutex_lock(mutex);
	tmp = *value;
	pthread_mutex_unlock(mutex);
	return (tmp);
}
