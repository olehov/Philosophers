/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:37:27 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/14 13:48:44 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_table			*table;

	if (argc == 5 || argc == 6)
	{
		table = table_init(argv, argc);
		if (table == NULL)
			return (EXIT_FAILURE);
		if (ft_pthreads_init(table) == -1)
			return (free_table(table), EXIT_FAILURE);
		start_controler(table);
		wait_all_threads(table);
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
