/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:43:19 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/23 14:25:41 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*space;
	unsigned int	i;
	size_t			s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	space = (char *)malloc (sizeof(char) * (len + 1));
	if (space == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		space [i] = s[start + i];
		i++;
	}
	space[i] = '\0';
	return (space);
}
// start >= ft_strlen(s)
// int main ()
// {
// 	printf("%s", ft_substr("openthewindowsweety", 30, 5));
// 	return (0);
// }
