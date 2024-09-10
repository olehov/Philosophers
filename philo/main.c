/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:43:50 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 15:25:03 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

// int	main(void)
// {
//     struct timeval start;
//     struct timeval end;
// 	// t_table	table;
//     long seconds;
//     long microseconds;
//     double elapsed;

// 	// table_init(&table, argc, argv);
//     gettimeofday(&start, NULL);
//     precise_usleep(500000);
//     gettimeofday(&end, NULL);
//     seconds = end.tv_sec - start.tv_sec;
//     microseconds = end.tv_usec - start.tv_usec;
//     elapsed = seconds + microseconds * 1e-6;
//     printf("Expected sleep duration: "RED"\t0.5"RESET" seconds\n");
//     printf("Actual sleep duration: "RED"\t\t%f"RESET" seconds\n\n", elapsed);
//     return (0);
// }

// int	main(int argc, char **argv)
int	main(void)
{
	t_table			table;
	int				argc;
	char	*argv[] = {"main.c", "2", "300", "200", "100", "7", NULL};

	argc = 5;
	if (argc == 5 || argc == 6)
	{
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
	return (0);
}
