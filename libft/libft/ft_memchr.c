/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:40:06 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/13 14:57:24 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem_s;
	unsigned char	uc;

	i = 0;
	mem_s = (unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (mem_s[i] == uc)
			return (&mem_s[i]);
		i++;
	}
	return (NULL);
}
