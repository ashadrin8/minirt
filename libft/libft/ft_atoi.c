/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:40:16 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/20 14:04:31 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c);

int	ft_atoi(const char *str)
{
	int	i;
	int	fin;
	int	minus;

	i = 0;
	fin = 0;
	minus = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = 1;
		i++;
	}
	while ((48 <= str[i] && str[i] <= 57) && (str[i] != '\0'))
	{
		fin = fin * 10 + (str[i] - 48);
		i++;
	}
	if (minus == 1)
		return (-fin);
	return (fin);
}

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f');
}
