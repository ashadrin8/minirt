/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:15:47 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/23 14:26:23 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*copying(unsigned char *dest_mem, unsigned char *src_mem, size_t n)
{
	size_t	i;

	i = 0;
	if ((dest_mem > src_mem) && (dest_mem < src_mem + n))
	{
		i = n;
		while (i > 0)
		{
			i--;
			dest_mem[i] = src_mem [i];
		}
	}
	else
	{
		while (i < n)
		{
			dest_mem[i] = src_mem[i];
			i++;
		}
	}
	return (dest_mem);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*dest_mem;
	unsigned char	*src_mem;

	if (len == 0 || (dest == src))
		return (dest);
	dest_mem = (unsigned char *)dest;
	src_mem = (unsigned char *)src;
	copying (dest_mem, src_mem, len);
	return (dest);
}
// if ((dest_mem > src_mem) && (dest_mem < src_mem + n))
// 	{
// 		i = n;
// 		while (i > 0)
// 		{
// 			i--;
// 			dest_mem[i] = src_mem [i];
// 		}
// 	}
// 	else
// 	{
// 		while (i < n)
// 		{
// 			dest_mem[i] = src_mem[i];
// 			i++;
// 		}
// 	}
// 	return (dest);
