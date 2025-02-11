/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:37:27 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/11 14:40:13 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

static bool	check_valid_input(char *argv[])
{
	size_t		i;
	size_t		j;
	const char	*err = RED "ERROR" RESET
		": arguments must contains only numbers\n";

	i = 1;
	j = 0;
	if (argv[i] == NULL)
		return (false);
	while (argv[i] != NULL)
	{
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(1, err, ft_strlen(err));
				return (0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (true);
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
