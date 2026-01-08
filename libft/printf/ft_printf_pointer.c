/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:53:49 by ashadrin          #+#    #+#             */
/*   Updated: 2025/08/11 21:39:08 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_pointer_address(unsigned long address, int *count);

int	ft_handle_pointer(va_list args)
{
	void			*ptr;
	unsigned long	address;
	int				count;

	ptr = va_arg(args, void *);
	if (!ptr)
	{
		if (write(1, NULL_STRING, NULL_STRING_LENGTH) == -1)
			return (-1);
		return (NULL_STRING_LENGTH);
	}
	address = (unsigned long)ptr;
	if (write(1, "0x", 2) == -1)
		return (-1);
	count = 2;
	ft_put_pointer_address(address, &count);
	return (count);
}

static void	ft_put_pointer_address(unsigned long address, int *count)
{
	char	digit;
	int		remainder;

	if (address >= 16)
	{
		ft_put_pointer_address(address / 16, count);
		if (*count == -1)
			return ;
	}
	remainder = address % 16;
	if (remainder < 10)
		digit = remainder + '0';
	else
		digit = remainder - 10 + 'a';
	if (write(1, &digit, 1) == -1)
	{
		*count = -1;
		return ;
	}
	(*count)++;
}
