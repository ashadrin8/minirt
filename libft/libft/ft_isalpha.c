/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 12:07:42 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/09 18:36:17 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int a)
{
	if ((65 <= a && a <= 90) || (97 <= a && a <= 122))
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int main (void)
// {
// 	int a = 6;

// 	printf("how many ducklings in the basket? %d", ft_isalpha(a));
// 	return (0);
// }
