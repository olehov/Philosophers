/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precise_usleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:53:15 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 14:08:56 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

int	precise_usleep(size_t usec)
{
	size_t	start;
	// size_t	elapsed;
	// size_t	rem;

	start = get_time(_MICROSECOND);
	while (get_time(_MICROSECOND) - start < usec)
	{
		// elapsed = get_time(_MICROSECOND) - start;
		// rem = usec - elapsed;
		// if (rem > 1000)
		// 	usleep(rem / 2);
	}
	return (0);
}
