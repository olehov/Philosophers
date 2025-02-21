/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:16:12 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/18 15:57:00 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_time_type
{
	_SECOND,
	_MILLISECOND,
	_MICROSECOND
}	t_time_type;

int		ft_isdigit(int c);

/**
 * @brief ft_strcpy - Copies a string from `src` to `dest` with a size limit.
 * 
 * @param dest Pointer to the destination buffer.
 * @param src Pointer to the source string.
 * @param dest_size Maximum number of characters to copy
 * (including null terminator).
 * 
 * @returns
 * The number of characters copied (excluding the null terminator).
 * SIZE_MAX if an error occurs (e.g., NULL pointers or `dest_size` is 0).
 * 
 * @note
 *  - If `dest` or `src` is NULL, or if `dest_size` is 0, returns `SIZE_MAX`.  
 *  - If `dest_size` is 1, sets `dest[0]` to `\0` and returns 0.
 *  - Copies up to `dest_size - 1` characters from `src` to `dest`,
 * 	ensuring null termination.
 */
size_t	ft_strcpy(char *dest, const char *src, size_t dest_size);
size_t	ft_strlen(const char *str);

size_t	ft_atoul(const char *str);
char	*ft_ultoa(size_t numb);

size_t	get_time(t_time_type time_type);

char	**ft_split(char const *s, char c);

char	*ft_join_and_free(char const *s1, char *s2);

void	precise_usleep(size_t usec);

#endif