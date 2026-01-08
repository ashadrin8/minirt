/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:19:13 by ashadrin          #+#    #+#             */
/*   Updated: 2025/08/11 15:08:12 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_specifiers(char symbol, va_list args);
int	ft_additional_printf(const char *format, va_list args);

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = ft_additional_printf(format, args);
	va_end(args);
	return (count);
}

int	ft_additional_printf(const char *format, va_list args)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format [i +1] != '\0')
		{
			i++;
			check = ft_format_specifiers(format[i], args);
			if (check == -1)
				return (-1);
			count += check;
		}
		else
		{
			if (write(1, &format[i], 1) == -1)
				return (-1);
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_format_specifiers(char symbol, va_list args)
{
	int	count;

	count = 0;
	if (symbol == 'c')
		return (ft_handle_char(args));
	else if (symbol == 's')
		return (ft_handle_string(args));
	else if (symbol == 'p')
		return (ft_handle_pointer(args));
	else if (symbol == 'd' || symbol == 'i')
		return (ft_handle_integer(args));
	else if (symbol == 'u')
		return (ft_handle_unsigned(args));
	else if (symbol == 'x')
		return (ft_handle_hex_low(args));
	else if (symbol == 'X')
		return (ft_handle_hex_up(args));
	else if (symbol == '%')
	{
		if (write (1, "%", 1) == -1)
			return (-1);
		return (1);
	}
	return (count);
}

// #include <stdio.h>
// #include <limits.h>
// #include <float.h>

// int main(void) {
//     int ret;

//     // Basic types
//     printf("Integer: %d\n", 42);
// 	ft_printf("Integer: %d\n", 42);
//     printf("Negative Integer: %d\n", -42);
// 	ft_printf("Negative Integer: %d\n", -42);
//     printf("Unsigned: %u\n", 3000000000U);
// 	ft_printf("Unsigned: %u\n", 3000000000U);
//     printf("Char: %c\n", 'A');
// 	ft_printf("Char: %c\n", 'A');
//     printf("String: %s\n", "Hello, world!");
// 	ft_printf("String: %s\n", "Hello, world!");

//     // Special characters
//     printf("Percent sign: %%\n");
// 	ft_printf("Percent sign: %%\n");
//     printf("Newline in string: Line1\nLine2\n");
// 	ft_printf("Newline in string: Line1\nLine2\n");

//     // Hex and Octal
//     printf("Hex lowercase: %x\n", 255);
// 	ft_printf("Hex lowercase: %x\n", 255);
//     printf("Hex uppercase: %X\n", 255);
// 	ft_printf("Hex uppercase: %X\n", 255);

//     // Pointers
//     int x = 42;
//     printf("Pointer: %p\n", (void*)&x);
// 	ft_printf("Pointer: %p\n", (void*)&x);

//     // Null string
//     char *null_str = NULL;
//     printf("Null string: %s\n", null_str);
// 	ft_printf("Null string: %s\n", null_str);

// 	//null pointer
// 	int *null = NULL;
// 	printf("Null pointer: %p\n", null);
// 	ft_printf("Null pointer: %p\n", null);

//     // Extreme values
//     printf("INT_MAX: %d\n", INT_MAX);
// 	ft_printf("INT_MAX: %d\n", INT_MAX);
//     printf("INT_MIN: %d\n", INT_MIN);
// 	ft_printf("INT_MIN: %d\n", INT_MIN);
//     printf("UINT_MAX: %u\n", UINT_MAX);
// 	ft_printf("UINT_MAX: %u\n", UINT_MAX);

//     // Return value of printf
//     ret = printf("Return value test: Hello\n");
//     printf("Previous printf returned: %d\n", ret);
// 	ret = ft_printf("Return value test: Hello\n");
//     ft_printf("Previous printf returned: %d\n", ret);

//     // Misuse cases (undefined behavior - uncomment with care)
//     // printf("Too many args: %d %d\n", 1);
//     // printf("Too few args: %d\n", 1, 2);
//     // printf("Invalid format: %q\n");

//     return 0;
// }
