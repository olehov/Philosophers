/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 04:10:34 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/12 17:17:27 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	set_bool(bool *var, sem_t *sem, bool value)
{
	sem_wait(sem);
	*var = value;
	sem_post(sem);
}

void	set_size_t(size_t *var, sem_t *sem, size_t value)
{
	sem_wait(sem);
	*var = value;
	sem_post(sem);
}
