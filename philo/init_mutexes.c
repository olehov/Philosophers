/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 13:05:57 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/13 13:51:33 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutexes	*init_mutexes(void)
{
	t_mutexes	*mutexes;

	mutexes = malloc(sizeof(t_mutexes));
	if (mutexes == NULL)
		return (NULL);
	if (pthread_mutex_init(&mutexes->can_print, NULL) == -1)
		return (free(mutexes), NULL);
	if (pthread_mutex_init(&mutexes->is_finished, NULL) == -1)
		return ((void)pthread_mutex_destroy(&mutexes->can_print),
			free(mutexes), NULL);
	if (pthread_mutex_init(&mutexes->print, NULL) == -1)
	{
		pthread_mutex_destroy(&mutexes->can_print);
		pthread_mutex_destroy(&mutexes->is_finished);
		return (free(mutexes), NULL);
	}
	if (pthread_mutex_init(&mutexes->start, NULL) == -1)
	{
		pthread_mutex_destroy(&mutexes->can_print);
		pthread_mutex_destroy(&mutexes->is_finished);
		pthread_mutex_destroy(&mutexes->print);
		return (free(mutexes), NULL);
	}
	return (mutexes);
}

