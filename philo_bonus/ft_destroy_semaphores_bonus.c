/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_destroy_semaphores_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:56:24 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/21 14:15:29 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_semaphore_bonus.h"

void	close_sem(sem_t *sem, char *name)
{
	if (sem == NULL)
		return ;
	sem_close(sem);
	sem_unlink(name);
}

void	ft_destroy_semaphores(t_semapores *sem)
{
	if (sem == NULL)
		return ;
	if (sem->can_print != SEM_FAILED)
		close_sem(sem->can_print, SEM_CAN_PRINT_NAME);
	if (sem->is_finished != SEM_FAILED)
		close_sem(sem->is_finished, SEM_IS_FINISHED_NAME);
	if (sem->print != SEM_FAILED)
		close_sem(sem->print, SEM_PRINT_NAME);
	if (sem->start != SEM_FAILED)
		close_sem(sem->start, SEM_START_NAME);
	if (sem->is_all_full != SEM_FAILED)
		close_sem(sem->is_all_full, SEM_IS_ALL_FULL);
	if (sem->is_died != SEM_FAILED)
		close_sem(sem->is_died, SEM_IS_DIED_NAME);
	free(sem);
}

void	ft_destroy_named_semaphore(t_named_sem *sem)
{
	if (sem == NULL)
		return ;
	if (sem->sem != SEM_FAILED)
	{
		close_sem(sem->sem, sem->name);
		sem_unlink(sem->name);
	}
	if (sem->name != NULL)
		free(sem->name);
	free(sem);
}
