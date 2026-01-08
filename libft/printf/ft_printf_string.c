/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:54:47 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/29 12:36:33 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_string(va_list args)
{
	char	*str;
	int		count;

	str = va_arg(args, char *);
	if (!str)
	{
		if (write (1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	count = 0;
	while (str[count] != '\0')
	{
		if (write(1, &str[count], 1) == -1)
			return (-1);
		count++;
	}
	return (count);
}
