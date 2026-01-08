/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:21:48 by ashadrin          #+#    #+#             */
/*   Updated: 2025/08/11 21:45:49 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

# if defined(__linux__)
#  define NULL_STRING "(nil)"
#  define NULL_STRING_LENGTH 5
# elif defined(__APPLE__)
#  define NULL_STRING "0x0"
#  define NULL_STRING_LENGTH 3
# endif

int	ft_printf(const char *format, ...);

int	ft_format_specifiers(char symbol, va_list args);
int	ft_handle_char(va_list args);
int	ft_handle_string(va_list args);
int	ft_handle_pointer(va_list args);
int	ft_handle_integer(va_list args);
int	ft_handle_unsigned(va_list args);
int	ft_handle_hex_low(va_list args);
int	ft_handle_hex_up(va_list args);

#endif
