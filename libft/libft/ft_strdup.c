/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 16:09:01 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/23 15:59:36 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*space;
	int		length;
	int		i;

	length = ft_strlen(s1);
	space = (char *)malloc((length + 1) * sizeof(char));
	if (space == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		space[i] = s1[i];
		i++;
	}
	space[i] = '\0';
	return (space);
}

// int	main(void)
// {
// 	char	*res;

// 	res = ft_strdup("Hallo that's a string");
// 	printf("%s\n", res);
// 	return (0);
// }
