/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 22:13:16 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/19 15:09:39 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int	in_set(char const *set, char k)
{
	int	h;

	h = 0;
	while (set[h] != '\0' && set[h] != k)
		h++;
	if (set[h] == k)
		return (1);
	else
		return (0);
}

static int	trimming(char const *s1, char const *set)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (in_set(set, s1[i]) == 1)
		i++;
	while (s1[len] != '\0')
		len++;
	len--;
	while (len >= i && in_set(set, s1[len]) == 1)
		len--;
	return (len - i + 1);
}

static int	start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (in_set(set, s1[i]) == 1)
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*space;
	int		i;
	int		k;
	int		len;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	len = trimming (s1, set);
	if (len <= 0)
		return (ft_strdup(""));
	space = (char *)malloc ((len + 1) * sizeof(char));
	if (space == NULL)
		return (NULL);
	k = 0;
	i = start(s1, set);
	while (k < len)
	{
		space[k] = s1[i];
		i++;
		k++;
	}
	space[k] = '\0';
	return (space);
}
