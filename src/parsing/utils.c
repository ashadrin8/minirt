/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 20:04:04 by ashadrin          #+#    #+#             */
/*   Updated: 2026/01/08 16:36:24 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_internal.h"

int	is_valid_rt(char *filename)
{
	int	i;
	
	i = ft_strlen(filename);
	i--;
	while (filename[i] == ' ')
		i--;
	if (filename[i] != 't')
		return (0);
	else 
		i--;
	if (filename[i] != 'r')
		return (0);
	else 
		i--;
	if (filename[i] != '.')
		return (0);
	return (1);
}

int	atoi_with_overflows(const char *str, int *value)
{
	int	i;
	int	fin;
	int	minus;

	i = 0;
	fin = 0;
	minus = 1;
	if (potential_int_check(str) == ERROR)
		return (printf("problem with check\n"), ERROR);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (fin > (INT_MAX / 10) || (fin == INT_MAX / 10
			&& (str[i] - '0') > 7))
			return (ERROR);
		fin = fin * 10 + (str[i] - '0');
		i++;
	}
	*value = fin * minus;
	printf("current result: %d\n", fin);
	return (SUCCESS);
}

int	ascii_to_double(char *str, double *value)
{
	int		i;
	double	fin;
	int		minus;
	double	factor;

	i = 0;
	fin = 0;
	minus = 1;
	factor = 0.1;
	if (potential_double_check(str) == ERROR)
		return (ERROR);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while (str[i] != '.' && str[i] != '\0')
	{
		fin = fin * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		while (str[i])
		{
			fin = fin + ((str[i] - '0') * factor);
			factor *= 0.1;
			i++;
		}
	}
	*value = fin * minus;
	printf("current result: %f\n", fin);
	return (SUCCESS);
}

int	potential_double_check(char *str)
{
	int	i;
	int	dots_total;
	int	digits;

	i = 0;
	dots_total = 0;
	digits = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && (str[i] != '.'))
			return (ERROR);
		if (str[i] == '.')
			dots_total++;
		if (ft_isdigit(str[i]))
			digits++;
		i++;
	}
	if (dots_total > 1)
		return (ERROR);
	if (!digits)
		return (ERROR);
	return (SUCCESS);
}

int	potential_int_check(const char *str)
{
	int i;
	int digits;
	
	i = 0;
	digits = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (printf("here darling!!, %d\n", str[i]), ERROR);
		if (ft_isdigit(str[i]))
			digits++;
		i++;
	}
	if (!digits)
		return (ERROR);
	return (SUCCESS);
}