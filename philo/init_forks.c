/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:55:29 by ogrativ           #+#    #+#             */
/*   Updated: 2025/01/07 13:41:47 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_fork	*init_fork(size_t id)
{
	t_fork	*fork;

	fork = malloc(sizeof(t_fork));
	if (fork == NULL)
		return (NULL);
	fork->id = id;
	if (pthread_mutex_init(&fork->fork, NULL) == -1)
		return (free(fork), NULL);
	return (fork);
}

static void	free_fork(t_fork *fork)
{
	if (fork == NULL)
		return ;
	fork->id = 0;
	pthread_mutex_destroy(&fork->fork);
	free(fork);
}

void	free_forks(t_fork **forks)
{
	size_t	i;

	if (forks == NULL)
		return ;
	i = 0;
	while (forks[i] != NULL)
	{
		free_fork(forks[i]);
		i++;
	}
	free(forks);
}

t_fork	**init_forks(size_t size)
{
	t_fork	**forks;
	size_t	i;

	i = 0;
	forks = (t_fork **)malloc(sizeof(t_fork) * (size + 1));
	if (forks == NULL)
		return (NULL);
	while (i < size)
	{
		forks[i] = init_fork(i);
		if (forks[i] == NULL)
			return (free_forks(forks), NULL);
		i++;
	}
	forks[size] = NULL;
	return (forks);
}
