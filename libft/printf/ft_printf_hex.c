/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:52:15 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/29 12:29:13 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_hex_output(unsigned int u, int format, int *count)
{
	char	digit;
	int		remainder;

	if (u >= 16)
	{
		ft_hex_output(u / 16, format, count);
		if (*count == -1)
			return ;
	}
	remainder = u % 16;
	if (remainder < 10)
		digit = remainder + '0';
	else if (format == 'a')
		digit = remainder - 10 + 'a';
	else
		digit = remainder - 10 + 'A';
	if (write(1, &digit, 1) == -1)
	{
		*count = -1;
		return ;
	}
	(*count)++;
}

int	ft_handle_hex_up(va_list args)
{
	unsigned int	u;
	int				count;

	count = 0;
	u = va_arg(args, unsigned int);
	ft_hex_output(u, 'A', &count);
	return (count);
}

int	ft_handle_hex_low(va_list args)
{
	unsigned int	u;
	int				count;

	count = 0;
	u = va_arg(args, unsigned int);
	ft_hex_output(u, 'a', &count);
	return (count);
}
