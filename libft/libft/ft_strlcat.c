/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:06:20 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/16 17:39:51 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	if (n == 0)
		return (ft_strlen(src));
	i = 0;
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (dlen >= n)
		return (n + slen);
	while (src[i] != '\0' && (dlen + i) < (n - 1))
	{
		dest[dlen + i] = src[i];
		i++;
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}

//always returns the length of what could have been

// int main ()
// {
// 	char dest[11] = "a";
//     printf("%zu", ft_strlcat(dest, "lorem", 15));
//     write(1, "\n", 1);
//     write(1, dest, 15);
// }
