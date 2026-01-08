/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinates_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:40:13 by ashadrin          #+#    #+#             */
/*   Updated: 2026/01/08 17:28:26 by ashadrin         ###   ########.fr       */
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
		printf("coordinates are as follows: %s, %s\n", string, number);
		if (coord_assign(number, coords, position) == ERROR)
			return (free(number), printf("ERROR ASSIGN\n"), ERROR);
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
	printf("was i here at all?\n");
	while (position <= 3)
	{
		start = i;
		while (string[i] != ',' && string[i])
			i++;
		len = i - start;
		number = ft_substr(string, start, len);
		if (vector_assign(number, vector, position) == ERROR)
			return (free(number), printf("no vector? huh?\n"), ERROR);
		free(number);
		position++;
		if (string[i] == ',')
			i++;
	}
	if (position != 4)
		return (printf("position not 4\n"), ERROR);
	return (SUCCESS);
}

int	vector_assign(char *number, t_coordinates *vector, int position)
{
	double	value;

	if (position > 3)
		return (ERROR);
	if (ascii_to_double(number, &value) == ERROR)
		return (printf("no ascii\n"), ERROR);
	if (value < -1.0 || value > 1.0)
		return (printf("AAAAAAA\n"), ERROR);
	if (position == 1)
		vector->x = value;
	if (position == 2)
		vector->y = value;
	if (position == 3)
		vector->z = value;
	return (printf("SUCCESS!!\n"), SUCCESS);
}
