/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:54:24 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/28 13:22:11 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_char(va_list args)
{
	int	c;
	int	count;

	c = va_arg(args, int);
	if (write(1, &c, 1) == -1)
		return (-1);
	count = 1;
	return (count);
}
