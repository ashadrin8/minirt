/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 13:39:49 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/23 14:25:20 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int x, size_t len)
{
	size_t			i;
	unsigned char	*memory;

	i = 0;
	memory = (unsigned char *)ptr;
	while (i < len)
	{
		memory[i] = (unsigned char)x;
		i++;
	}
	return (ptr);
}

// #include <unistd.h>
// int main ()
// {
// 	int arr1[] = {3,4};
// 	int arr2[] = {1,2};
// 	memset(arr1, 0, 2 * sizeof(int));
// 	printf("%d %d", arr1[0]);
// 	return (0);
// }
// memset (arr1 (the place in memory that you want to set from),
// 0 (the value),
// 2 * sizeof(int) (how many bytes you want to set));
//ptr -- starting address of memory to be filled
// x -- value to be filled
// n -- number of bytes to be filled starting from ptr to be filled
