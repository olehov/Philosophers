/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:22:06 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/10 15:49:10 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static bool	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static bool	check_valid_long(char *str, int i)
{
	const char	*long_max_str = "9223372036854775807";
	size_t		long_max_len;
	size_t		len;
	int			j;

	long_max_len = 19;
	len = ft_strlen(str + i);
	if (len > long_max_len)
		return (print_error_with_endl("Argument exceeds LONG_MAX"), false);
	if (len == long_max_len)
	{
		j = 0;
		while (str[i] != '\0' && long_max_str[j] != '\0')
		{
			if (str[i] > long_max_str[j] || !is_digit(str[i]))
				return (false);
			i++;
			j++;
		}
	}
	return (true);
}

long	ft_atol(char *str)
{
	long	number;
	int		i;

	number = 0;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
		return (print_error_with_endl("Argument can't be negative"), 0);
	if (str[i] == '+')
		i++;
	if (!check_valid_long(str, i))
		return (print_error_with_endl(
				"Argument exceeds LONG_MAX or contains non-numeric characters"
			), 0);
	while (str[i] != '\0' && is_digit(str[i]))
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number);
}
