/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:52:51 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/21 16:52:30 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <string.h>

void	free_table(t_table *table)
{
	if (table == NULL)
		return ;
	table->can_print = 0;
	table->number_of_philos = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	ft_destroy_semaphores(table->semaphores);
	if (table->forks != SEM_FAILED)
		close_sem(table->forks, SEM_FORKS_NAME);
	if (table->pids != NULL)
		free(table->pids);
	free(table);
}

static size_t	set_size_t_values(char **args, int argc, t_table *table)
{
	size_t	max_meals;

	table->number_of_philos = ft_atoul(args[1]);
	table->time_to_die = ft_atoul(args[2]);
	table->time_to_eat = ft_atoul(args[3]);
	table->time_to_sleep = ft_atoul(args[4]);
	if (argc == 6)
		max_meals = ft_atoul(args[5]);
	else
		max_meals = 0;
	return (max_meals);
}

t_table	*table_init(char *args[], int argc)
{
	t_table		*table;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	table->pids = NULL;
	table->can_print = true;
	table->max_meals = set_size_t_values(args, argc, table);
	if (table->time_to_die < table->time_to_eat || table->time_to_die < 1
		|| table->time_to_eat < 1 || table->time_to_sleep < 1)
		return (free_table(table), NULL);
	table->semaphores = ft_init_semaphores();
	if (table->semaphores == NULL)
		return (free_table(table), NULL);
	table->forks = sem_open(SEM_FORKS_NAME, O_CREAT, 0666,
			table->number_of_philos);
	if (table->forks == SEM_FAILED)
		return (free_table(table), NULL);
	table->pids = malloc(sizeof(pid_t) * table->number_of_philos);
	if (table->pids == NULL)
		return (NULL);
	return (table);
}
