/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 11:41:27 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/14 18:52:05 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t l)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (src[len])
		len++;
	if (l == 0)
		return (len);
	i = 0;
	while ((i < l - 1) && (src[i] != '\0'))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
// int main ()
// {
// 	printf("%zu", ft_strlcpy("fjsior", "kkk", 2));
// 	return (0);
// }
// size < len_src
