/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 14:52:51 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/13 13:52:49 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	free_table(t_table *table)
{
	if (table == NULL)
		return ;
	table->can_print = 0;
	table->is_finished = 0;
	table->ready_to_start = 0;
	table->number_of_philos = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	destroy_mutexes(table->mutexes);
	if (table->philosophers != NULL)
		free_philos(table->philosophers);
	if (table->forks != NULL)
		free_forks(table->forks);
	free(table);
}

static void	set_bool_values(t_table *table)
{
	table->can_print = true;
	table->is_finished = false;
	table->ready_to_start = false;
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

void	assign_forks(t_table *table)
{
	size_t	i;
	size_t	philos_number;

	i = 0;
	while (i < table->number_of_philos)
	{
		philos_number = table->number_of_philos;
		table->philosophers[i]->left_fork
			= table->forks[(i + 1) % philos_number];
		table->philosophers[i]->rigth_fork = table->forks[i];
		i++;
	}
}

t_table	*table_init(char *args[], int argc)
{
	t_table		*table;
	size_t		max_meals;

	table = malloc(sizeof(t_table));
	if (table == NULL)
		return (NULL);
	set_bool_values(table);
	max_meals = set_size_t_values(args, argc, table);
	if (table->time_to_die < table->time_to_eat || table->time_to_die < 1
		|| table->time_to_eat < 1)
		return (free_table(table), NULL);
	table->mutexes = init_mutexes();
	if (table->mutexes == NULL)
		return (free_table(table), NULL);
	table->philosophers = philos_init(max_meals, table);
	if (table->philosophers == NULL)
		return (free_table(table), NULL);
	table->forks = init_forks(table->number_of_philos);
	if (table->forks[0] == NULL)
		return (free_table(table), NULL);
	assign_forks(table);
	return (table);
}
