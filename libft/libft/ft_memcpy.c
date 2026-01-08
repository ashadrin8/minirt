/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:05:35 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/23 16:17:25 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_mem;
	unsigned char	*src_mem;

	i = 0;
	dest_mem = (unsigned char *)dest;
	src_mem = (unsigned char *)src;
	if (!dest && !src)
		return (dest);
	while (i < n)
	{
		dest_mem[i] = src_mem[i];
		i++;
	}
	return (dest);
}
