/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_semaphores_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:46:45 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/19 16:58:37 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_semaphore_bonus.h"
#include "philo_bonus.h"

static void	fill_nulls(t_semapores *sem)
{
	if (sem == NULL)
		return ;
	sem->can_print = SEM_FAILED;
	sem->is_finished = SEM_FAILED;
	sem->print = SEM_FAILED;
	sem->start = SEM_FAILED;
	sem->is_all_full = SEM_FAILED;
	sem->is_died = SEM_FAILED;
}

t_semapores	*ft_init_semaphores(void)
{
	t_semapores	*sem;

	sem = malloc(sizeof(t_semapores));
	if (sem == NULL)
		return (NULL);
	fill_nulls(sem);
	sem->can_print = sem_open(SEM_CAN_PRINT_NAME, O_CREAT, 0666, 1);
	if (sem->can_print == SEM_FAILED)
		return (free(sem), NULL);
	sem->is_finished = sem_open(SEM_IS_FINISHED_NAME, O_CREAT, 0666, 0);
	if (sem->is_finished == SEM_FAILED)
		return (ft_destroy_semaphores(sem), NULL);
	sem->print = sem_open(SEM_PRINT_NAME, O_CREAT, 0666, 1);
	if (sem->print == SEM_FAILED)
		return (ft_destroy_semaphores(sem), NULL);
	sem->start = sem_open(SEM_START_NAME, O_CREAT, 0666, 0);
	if (sem->start == SEM_FAILED)
		return (ft_destroy_semaphores(sem), NULL);
	sem->is_all_full = sem_open(SEM_IS_ALL_FULL, O_CREAT, 0666, 0);
	if (sem->is_all_full == SEM_FAILED)
		return (ft_destroy_semaphores(sem), NULL);
	sem->is_died = sem_open(SEM_IS_DIED_NAME, O_CREAT, 0666, 0);
	if (sem->is_died == SEM_FAILED)
		return (ft_destroy_semaphores(sem), NULL);
	return (sem);
}

t_named_sem	*ft_init_named_semaphore(const char *name, size_t id)
{
	t_named_sem	*sem;

	if (name == NULL)
		return (NULL);
	sem = malloc(sizeof(t_named_sem));
	if (sem == NULL)
		return (NULL);
	sem->name = ft_join_and_free(name, ft_ultoa(id));
	if (sem->name == NULL)
		return (free(sem), NULL);
	sem->sem = sem_open(sem->name, O_CREAT, 0666, 1);
	if (sem->sem == SEM_FAILED)
		return (ft_destroy_named_semaphore(sem), NULL);
	return (sem);
}
