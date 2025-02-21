/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_and_free_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogrativ <ogrativ@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:55:10 by ogrativ           #+#    #+#             */
/*   Updated: 2025/02/17 17:21:39 by ogrativ          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_bonus.h"
#include <stdlib.h>

char	*ft_join_and_free(char const *s1, char *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	new_str_len;
	size_t	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new_str_len = s1_len + s2_len;
	new_str = malloc(sizeof(char) * (new_str_len + 1));
	if (new_str == NULL)
		return (NULL);
	while (i < s1_len)
	{
		new_str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
		new_str[s1_len++] = s2[i++];
	new_str[s1_len] = '\0';
	return (free(s2), new_str);
}
