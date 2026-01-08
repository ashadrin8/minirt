/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 13:11:21 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/12 13:31:14 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str, const char *stri, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && str[i] != '\0' && stri[i] != '\0' && str[i] == stri[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)str[i] - (unsigned char)stri[i]);
}

// int main ()
// {
// 	printf("%d", ft_strncmp("NULL", "\0", 3));
// 	return (0);
// }
