/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:01:57 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/15 13:24:22 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	i;

	if (n == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write (fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	i = n % 10 + '0';
	write(fd, &i, 1);
}

// int main()
// {
// 	ft_putnbr_fd(123, 1);
// }
// {
// 	int i;
// 	char *ascii_now;

// 	i = 0;
// 	ascii_now = ft_itoa(n);
// 	while (ascii_now[i])
// 	{
// 		write (fd, &ascii_now[i], 1);
// 		i++;
// 	}
// }
