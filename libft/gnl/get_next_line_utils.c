/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:15:56 by ashadrin          #+#    #+#             */
/*   Updated: 2026/01/07 14:49:06 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	if (!str)
		return (NULL);
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

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*space;
	int		i;
	int		p;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	space = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (space == NULL)
		return (NULL);
	i = 0;
	p = 0;
	while (s1[i] != '\0')
		space[p++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		space[p++] = s2[i++];
	space[p] = '\0';
	return (space);
}
