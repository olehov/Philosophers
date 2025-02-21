/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:37:27 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/21 17:31:08 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <unistd.h>
#include <sys/wait.h>

static bool	check_valid_input(char *argv[])
{
	size_t		i;
	size_t		j;
	const char	*err = RED "ERROR" RESET
		": arguments must contains only numbers\n";

	i = 1;
	if (argv[i] == NULL)
		return (false);
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(1, err, ft_strlen(err));
				return (0);
			}
			j++;
		}
		i++;
	}
	return (true);
}

int	ft_processes_start(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->number_of_philos)
	{
		table->pids[i] = fork();
		if (table->pids[i] < 0)
			return (-1);
		if (table->pids[i] == 0)
		{
			start_simulation(table, i + 1);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	i = 0;
	while (i < table->number_of_philos)
	{
		sem_post(table->semaphores->start);
		i++;
	}
	return (0);
}

void	kill_pids(t_table *table)
{
	size_t	i;

	i = 0;
	if (table->pids == NULL)
		return ;
	while (i < table->number_of_philos)
	{
		kill(table->pids[i], SIGINT);
		i++;
	}
}

void	wait_all_processes(t_table *table)
{
	size_t	i;
	int		status;

	i = 0;
	precise_usleep(10);
	i = 0;
	while (i < table->number_of_philos)
	{
		waitpid(table->pids[i], &status, 0);
		i++;
	}
	pthread_join(table->id, NULL);
}

int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc == 5 || argc == 6)
	{
		if (!check_valid_input(argv))
			return (EXIT_FAILURE);
		table = table_init(argv, argc);
		if (table == NULL)
			return (EXIT_FAILURE);
		if (ft_processes_start(table) == -1)
		{
			printf("ERROR could not start process\n");
			return (free_table(table), EXIT_FAILURE);
		}
		start_controler(table);
		wait_all_processes(table);
		free_table(table);
	}
	else
	{
		printf("Usage: number_of_philosophers time_to_die time_to_eat %s",
			"time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
