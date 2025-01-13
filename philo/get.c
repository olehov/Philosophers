/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 04:14:49 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/08 14:34:39 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_bool(bool *var, pthread_mutex_t *mutex)
{
	bool	tmp;

	if (var == NULL || mutex == NULL)
		return (false);
	pthread_mutex_lock(mutex);
	tmp = *var;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

size_t	get_size_t(size_t *var, pthread_mutex_t *mutex)
{
	size_t	tmp;

	if (var == NULL || mutex == NULL)
		return (0);
	pthread_mutex_lock(mutex);
	tmp = *var;
	pthread_mutex_unlock(mutex);
	return (tmp);
}
