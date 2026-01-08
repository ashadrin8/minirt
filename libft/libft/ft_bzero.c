/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 13:31:40 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/19 15:36:32 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*memory;

	i = 0;
	memory = (unsigned char *)s;
	while (i < n)
	{
		memory[i] = 0;
		i++;
	}
}

// int main ()
// {
// 	int arr[] = {5, 5, 7, 6, 8};
// 	*ft_bzero (arr, sizeof(arr));
// 	printf("%d", arr);
// 	return (0);
// }
