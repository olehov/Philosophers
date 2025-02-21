/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 04:14:49 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/12 15:08:30 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	get_bool(bool *var, sem_t *sem)
{
	bool	tmp;

	if (var == NULL || sem == NULL)
		return (false);
	sem_wait(sem);
	tmp = *var;
	sem_post(sem);
	return (tmp);
}

size_t	get_size_t(size_t *var, sem_t *sem)
{
	size_t	tmp;

	if (var == NULL || sem == NULL)
		return (0);
	sem_wait(sem);
	tmp = *var;
	sem_post(sem);
	return (tmp);
}
