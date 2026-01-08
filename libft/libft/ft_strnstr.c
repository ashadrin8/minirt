/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:58:16 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/20 15:01:05 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	p;

	if (haystack == NULL && needle != NULL && len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while ((haystack[i] != '\0') && (i < len))
	{
		p = 0;
		while (haystack[i + p] == needle[p]
			&& needle[p] != '\0' && (i + p) < len)
			p++;
		if (needle[p] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main ()
// {
// 	char *haystack = "don't make me build a fruit trap";
// 	char *needle = "bui";
// 	// printf("%s", ft_strnstr(haystack, needle, 4));
// 	strnstr(NULL, NULL, 3);
// 	return (0);
// }
