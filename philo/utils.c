/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:45:27 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 15:43:28 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (str == NULL)
	{
		return (0);
	}
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	print_error_with_endl(char *error)
{
	if (error == NULL)
	{
		printf(RED "ERROR: " RESET "Message empty");
	}
	else
	{
		printf(RED "ERROR: " RESET "%s\n", error);
	}
}

void	*safe_malloc(size_t byte)
{
	void	*value;

	value = malloc(byte);
	if (value == NULL)
	{
		print_error_with_endl("Failed allocate memory");
		return (NULL);
	}
	return (value);
}

void	table_destroy(t_table *table)
{
	int	i;

	i = -1;
	if (table == NULL)
	{
		return ;
	}
	if (table->forks != NULL)
	{
		while (++i < table->number_of_philo)
		{
			pthread_mutex_destroy(&table->forks[i].mutex);
		}
		free(table->forks);
	}
	if (table->philosophers != NULL)
	{
		free(table->philosophers);
	}
}

long	get_time(t_time_type time_type)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
	{
		return (0);
	}
	if (time_type == _SECOND)
	{
		return ((tv.tv_sec + (tv.tv_usec / 1000000.0)));
	}
	else if (time_type == _MILLISECOND)
	{
		return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
	}
	else if (time_type == _MICROSECOND)
	{
		return (((tv.tv_sec * 1000000) + tv.tv_usec));
	}
	else
	{
		print_error_with_endl("Invalid time type");
		return (0);
	}
}
