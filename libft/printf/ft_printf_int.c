/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:50:36 by ashadrin          #+#    #+#             */
/*   Updated: 2025/08/11 21:35:50 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_digits_recursive(int i, int *count)
{
	char	digit;

	if (i >= 10)
	{
		ft_put_digits_recursive(i / 10, count);
		if (*count == -1)
			return ;
	}
	digit = (i % 10) + '0';
	if (write (1, &digit, 1) == -1)
	{
		*count = -1;
		return ;
	}
	(*count)++;
}

int	ft_handle_integer(va_list args)
{
	int	i;
	int	count;

	i = va_arg(args, int);
	if (i == -2147483648)
	{
		if (write (1, "-2147483648", 11) == -1)
			return (-1);
		count = 11;
		return (count);
	}
	count = 0;
	if (i < 0)
	{
		if (write (1, "-", 1) == -1)
			return (-1);
		i = -i;
		count++;
	}
	ft_put_digits_recursive(i, &count);
	return (count);
}

void	ft_put_digits_recursive_unsigned(unsigned int u, int *count)
{
	char	digit;

	if (u >= 10)
	{
		ft_put_digits_recursive_unsigned(u / 10, count);
		if (*count == -1)
			return ;
	}
	digit = u % 10 + '0';
	if (write(1, &digit, 1) == -1)
	{
		*count = -1;
		return ;
	}
	(*count)++;
}

int	ft_handle_unsigned(va_list args)
{
	unsigned int	u;
	int				count;

	count = 0;
	u = va_arg(args, unsigned int);
	ft_put_digits_recursive_unsigned(u, &count);
	return (count);
}
