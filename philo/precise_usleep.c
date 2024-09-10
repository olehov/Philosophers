/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precise_usleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:53:15 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 15:41:25 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

int	precise_usleep(size_t usec)
{
	size_t	start;

	start = get_time(_MICROSECOND);
	while (get_time(_MICROSECOND) - start < usec)
		;
	return (0);
}
