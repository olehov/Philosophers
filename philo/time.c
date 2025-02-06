/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 12:52:15 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/06 16:45:38 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_time(t_time_type time_type)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	if (time_type == _SECOND)
		return (tv.tv_sec);
	else if (time_type == _MILLISECOND)
		return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
	else if (time_type == _MICROSECOND)
		return (((tv.tv_sec * 1000000) + tv.tv_usec));
	else
		return (0);
}

// void	precise_usleep(size_t usec)
// {
// 	size_t	start;
// 	size_t	elapsed;

// 	start = get_time(_MILLISECOND);
// 	elapsed = get_time(_MILLISECOND) - start;
// 	while (usec > elapsed)
// 	{
// 		elapsed = get_time(_MILLISECOND) - start;
// 		if (usec - elapsed > 1)
// 			usleep(1000);
// 	}
// }

void	precise_usleep(size_t msec)
{
	size_t	start;
	size_t	elapsed;

	start = get_time(_MILLISECOND);
	elapsed = 0;
	while (elapsed < msec)
	{
		elapsed = get_time(_MILLISECOND) - start;
		if (msec - elapsed > 5)
			usleep(1000);
		else
			usleep(100);
	}
}
