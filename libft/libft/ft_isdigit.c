/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:25:30 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/09 18:37:23 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int n)
{
	if ('0' <= n && n <= '9')
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// int main (void)
// {
// 	int n = 'p';
// 	printf ("%d", ft_isdigit(n));
// 	return (0);
// }
