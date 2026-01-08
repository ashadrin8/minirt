/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 13:11:42 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/20 18:22:01 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*space;

	if (count && size > ULONG_MAX / count)
		return (NULL);
	space = (char *)malloc (count * size);
	if (space == NULL)
		return (NULL);
	ft_memset(space, 0, size * count);
	return (space);
}
