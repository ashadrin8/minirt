/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:14:06 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/23 13:54:10 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*mem_s1;
	unsigned char	*mem_s2;

	mem_s1 = (unsigned char *)s1;
	mem_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n && mem_s1[i] == mem_s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)mem_s1[i] - (unsigned char)mem_s2[i]);
}
