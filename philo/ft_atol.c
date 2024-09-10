/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:22:06 by ogrativ           #+#    #+#             */
/*   Updated: 2024/09/04 13:00:55 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "philo.h"

// static bool	is_space(char c)
// {
// 	return (c == 9 || (c > 10 && c < 14));
// }

// static bool	is_digit(char c)
// {
// 	return (c >= '0' && c <= '9');
// }

// static bool	check_valid_size_t(char *str, int i)
// {
// 	size_t		zu_max_len;
// 	size_t		len;
// 	int			j;
// 	const char	*zu_max = "9223372036854775807";

// 	i = 0;
// 	j = 0;
// 	zu_max_len = 19;
// 	len = ft_strlen(str);
// 	if (len - i > zu_max_len)
// 		return (print_error_with_endl("argument more than size_t max value"),
// 			false);
// 	if (len == zu_max_len)
// 	{
// 		while (str[i] != '\0' && zu_max[j] != '\0')
// 		{
// 			if (str[i] > zu_max[j] || !is_digit(str[i]))
// 				return (false);
// 			i++;
// 			j++;
// 		}
// 	}
// 	return (true);
// }

// long	ft_atol(char *str)
// {
// 	long	number;
// 	int		i;

// 	i = 0;
// 	number = 0;
// 	while (is_space(str[i++]))
// 	{
// 	}
// 	if (str[i] == '-')
// 		return (print_error_with_endl("Argument can't be negative"), 0);
// 	if (str[i] == '+')
// 		i++;
// 	if (!check_valid_size_t(str, i))
// 		return (print_error_with_endl("Argument more than max or not numeric"),
// 			0);
// 	while (str[i] != '\0')
// 	{
// 		number += str[i] - '0';
// 		if (str[i + 1] != '\0')
// 		{
// 			number *= 10;
// 		}
// 		i++;
// 	}
// 	return (number);
// }

#include "philo.h"
#include <limits.h> // Для LONG_MAX

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
	size_t		long_max_len = 19; // Довжина LONG_MAX
	size_t		len;
	int			j;

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
	long	number = 0;
	int		i = 0;

	// Пропустити пробіли
	while (is_space(str[i]))
		i++;
	
	// Обробка негативного значення
	if (str[i] == '-')
		return (print_error_with_endl("Argument can't be negative"), 0);
	
	// Пропустити знак '+', якщо він є
	if (str[i] == '+')
		i++;
	
	// Перевірка на правильний розмір і наявність тільки чисел
	if (!check_valid_long(str, i))
		return (print_error_with_endl("Argument exceeds LONG_MAX or contains non-numeric characters"), 0);
	
	// Преобразування рядка в число
	while (str[i] != '\0' && is_digit(str[i]))
	{
		number = number * 10 + (str[i] - '0');
		i++;
	}
	return (number);
}
