/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:44:43 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/16 22:45:40 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_internal.h"

void	further_ascii_double(char *str, int *i, double *fin)
{
	double	factor;

	factor = 0.1;
	while (str[*i] != '.' && str[*i] != '\0')
	{
		*fin = *fin * 10 + (str[*i] - '0');
		(*i)++;
	}
	if (str[*i] == '.')
	{
		(*i)++;
		while (str[*i])
		{
			*fin = *fin + ((str[*i] - '0') * factor);
			factor *= 0.1;
			(*i)++;
		}
	}
}

int	ascii_to_double(char *str, double *value)
{
	int		i;
	double	fin;
	int		minus;

	i = 0;
	fin = 0;
	minus = 1;
	if (potential_double_check(str) == ERROR)
		return (ERROR);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	further_ascii_double(str, &i, &fin);
	*value = fin * minus;
	return (SUCCESS);
}
