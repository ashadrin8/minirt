/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 19:29:35 by ashadrin          #+#    #+#             */
/*   Updated: 2025/07/13 13:25:40 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	how_many_digits(int n);
static void	filling(char *str, int n, int len);

char	*ft_itoa(int n)
{
	int		digits;
	char	*space;

	if (n == 0)
	{
		space = (char *)malloc(sizeof(char) * 2);
		if (space == NULL)
			return (NULL);
		space[0] = '0';
		space[1] = '\0';
		return (space);
	}
	digits = how_many_digits(n);
	space = (char *)malloc((digits + 1) * sizeof(char));
	if (space == NULL)
		return (NULL);
	filling (space, n, digits + 1);
	return (space);
}

static int	how_many_digits(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	filling(char *str, int n, int len)
{
	int	i;

	i = len - 2;
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str [i] = '8';
			n = -214748364;
			i--;
		}
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	str[len - 1] = '\0';
}
// static char	*temporary_thing (int n)
// {
// 	int i;
// 	char *str;
// 	int len;

// 	i = 0;
// 	len = how_many_digits(n);
// 	str = (char *)malloc (len + 1 * sizeof(char));
// 	if (n < 0)
// 	{
// 		str [len] = '-';
// 		n *= -1;
// 	}
// 	while (n > 0)
// 	{
// 		str[i] = (n % 10) + 48;
// 		n = n / 10;
// 		i++;
// 	}
// 	return (str);
// }

// temp = temporary_thing (n);
// 	i = 0;
// 	if (n < 0)
// 	{
// 		space[i] = '-';
// 		i++;
// 	}
// 	while (digits != 0)
// 	{
// 		space[i] = temp[digits - 1];
// 		i++;
// 		digits--;
// 	}

// #include <limits.h>
// #include <stdlib.h>
// int main()
// {
// 	char *s = ft_itoa(-992);
// 	printf("%s\n", s);
// 	printf("%d", how_many_digits (-953));
// 	return (0);
// }
