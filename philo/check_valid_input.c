/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:03:24 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/11 14:52:46 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "philo.h"

static int	check_if_all_integers(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (j < argc)
	{
		while (argv[j][i] != '\0')
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
			{
				printf("Character not decimal\n");
				return (-1);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

static int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 1)
		{
			printf("Argument less than 1\n");
			return (-1);
		}
		i++;
	}
	return (1);
}

int	check_valid_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die %s%s", argv[0],
			"time_to_eat time_to_sleep ",
			"[number_of_times_each_philosopher_must_eat]\n");
		return (-1);
	}
	if (check_input(argc, argv) == -1
		|| check_if_all_integers(argc, argv) == -1)
	{
		return (-1);
	}
	return (1);
}
