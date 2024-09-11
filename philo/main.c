/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:43:50 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/11 16:08:35 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table			table;

	if (argc == 5 || argc == 6)
	{
		if (check_valid_input(argc, argv) == -1)
			return (EXIT_FAILURE);
		table_init(&table, argc, argv);
		start_simulation(&table);
		table_destroy(&table);
	}
	else
	{
		printf("Usage: number_of_philosophers time_to_die time_to_eat %s",
			"time_to_sleep [number_of_times_each_philosopher_must_eat]");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
