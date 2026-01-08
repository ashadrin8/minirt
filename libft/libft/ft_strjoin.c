/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:13:48 by ashadrin          #+#    #+#             */
/*   Updated: 2025/08/04 15:46:50 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	le(char const *s1, char const *s2)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (s1[i] != '\0')
		i++;
	while (s2[p] != '\0')
	{
		i++;
		p++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*space;
	int		i;
	int		p;

	if (!s1 || !s2)
		return (NULL);
	space = (char *)malloc ((le(s1, s2) + 1) * sizeof(char));
	if (space == NULL)
		return (NULL);
	i = 0;
	p = 0;
	while (s1[i] != '\0')
	{
		space[p++] = s1[i++];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		space[p] = s2[i];
		p++;
		i++;
	}
	space[p] = '\0';
	return (space);
}
