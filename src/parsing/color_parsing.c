/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:39:22 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/12 18:51:36 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_internal.h"

//231,0,14
int	validate_and_store_color(char *string, t_color *color)
{
	int		position;
	int		i;
	int		start;
	char	*number;
	char	len;

	position = 1;
	i = 0;
	printf("string is like this: %s\n", string);
	while (1)
	{
		start = i;
		while (string[i] != ',' && string[i] != '\0')
			i++;
		len = i - start;
		number = ft_substr(string, start, len);
		if (color_assign(number, color, position) == ERROR)
			return (free(number), ERROR);
		printf("Extracted color part: '%s' (position %d)\n", number, position);
		free(number);
		position++;
		if (string[i] == '\0')
			break ;
		i++;
	}
	if (position != 4)
		return (ERROR);
	return (SUCCESS);
}

int	color_assign(char *number, t_color *color, int position)
{
	int	value;
	
	if (position > 3)
		return (ERROR);
	if (atoi_with_overflows(number, &value) == ERROR)
	{
		printf("we went till here and the value is %d\n the number was %s by the way\n", value, number);
		return (ERROR);
	}
	if (value < 0 || value > 255)
		return (ERROR);
	if (position == 1)
		color->red = value;
	if (position == 2)
		color->green = value;
	if (position == 3)
		color->blue = value;
	return (SUCCESS);
}
