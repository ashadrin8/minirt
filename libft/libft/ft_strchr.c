/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:25:06 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/15 12:01:17 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	c = (unsigned char)c;
	i = 0;
	while ((str[i] != '\0') && (str[i] != c))
		i++;
	if (str[i] == c)
		return ((char *)&str[i]);
	if (c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
