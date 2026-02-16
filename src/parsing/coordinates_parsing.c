/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:40:13 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/16 20:20:10 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_internal.h"

int	validate_and_store_coordinates(char *string, t_coordinates *coords)
{
	int		position;
	int		i;
	int		start;
	int		len;
	char	*number;

	position = 1;
	i = 0;
	while (string[i])
	{
		start = i;
		while (string[i] != ',' && string[i])
			i++;
		len = i - start;
		number = ft_substr(string, start, len);
		if (coord_assign(number, coords, position) == ERROR)
			return (free(number), ERROR);
		free(number);
		position++;
		if (string[i] == ',')
			i++;
	}
	if (position != 4)
		return (ERROR);
	return (SUCCESS);
}

int	coord_assign(char *number, t_coordinates *coords, int position)
{
	double	value;

	if (position > 3)
		return (ERROR);
	if (ascii_to_double(number, &value) == ERROR)
		return (ERROR);
	if (position == 1)
		coords->x = value;
	if (position == 2)
		coords->y = value;
	if (position == 3)
		coords->z = value;
	return (SUCCESS);
}

int	validate_and_store_vector(char *string, t_coordinates *vector)
{
	int		position;
	int		i;
	int		start;
	int		len;
	char	*number;

	position = 1;
	i = 0;
	while (position <= 3)
	{
		start = i;
		while (string[i] != ',' && string[i])
			i++;
		len = i - start;
		number = ft_substr(string, start, len);
		if (vector_assign(number, vector, position) == ERROR)
			return (free(number), ERROR);
		free(number);
		position++;
		if (string[i] == ',')
			i++;
	}
	if (position != 4)
		return (ERROR);
	return (SUCCESS);
}

int	vector_assign(char *number, t_coordinates *vector, int position)
{
	double	value;

	if (position > 3)
		return (ERROR);
	if (ascii_to_double(number, &value) == ERROR)
		return (ERROR);
	if (value < -1.0 || value > 1.0)
		return (ERROR);
	if (position == 1)
		vector->x = value;
	if (position == 2)
		vector->y = value;
	if (position == 3)
		vector->z = value;
	return (SUCCESS);
}
