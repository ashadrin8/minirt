/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 20:32:19 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/16 20:41:17 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_internal.h"

int	validate_store_sphere(t_parsing *p, t_scene *s)
{
	double	diameter;

	if (p->position == 4)
		return (ERROR);
	if (p->position == 1)
	{
		if (validate_and_store_coordinates(p->parameter,
				&s->last_sphere->center) == ERROR)
			return (ERROR);
	}
	if (p->position == 2)
	{
		if (ascii_to_double(p->parameter, &diameter) == ERROR)
			return (ERROR);
		if (diameter <= 0.0)
			return (ERROR);
		s->last_sphere->diameter = diameter;
	}
	if (p->position == 3)
		return (validate_and_store_color(p->parameter, &s->last_sphere->color));
	return (SUCCESS);
}

int	validate_store_plane(t_parsing *p, t_scene *s)
{
	if (p->position == 4)
		return (ERROR);
	if (p->position == 1)
		return (validate_and_store_coordinates(p->parameter,
				&s->last_plane->point));
	if (p->position == 2)
		return (validate_and_store_vector(p->parameter,
				&s->last_plane->vector));
	if (p->position == 3)
		return (validate_and_store_color(p->parameter,
				&s->last_plane->color));
	return (SUCCESS);
}

int	validate_cylinder_diameter(t_parsing *p, t_scene *s)
{
	if (ascii_to_double(p->parameter, &p->number) == ERROR)
		return (ERROR);
	if (p->number <= 0.0)
		return (ERROR);
	s->last_cylinder->diameter = p->number;
	return (SUCCESS);
}

int	validate_store_cylinder(t_parsing *p, t_scene *s)
{
	if (p->position == 6)
		return (ERROR);
	if (p->position == 1)
		return (validate_and_store_coordinates(p->parameter,
				&s->last_cylinder->center));
	if (p->position == 2)
		return (validate_and_store_vector(p->parameter,
				&s->last_cylinder->vector));
	if (p->position == 3)
		return (validate_cylinder_diameter(p, s));
	if (p->position == 4)
	{
		if (ascii_to_double(p->parameter, &p->number) == ERROR)
			return (ERROR);
		if (p->number <= 0.0)
			return (ERROR);
		s->last_cylinder->height = p->number;
	}
	if (p->position == 5)
		return (validate_and_store_color(p->parameter,
				&s->last_cylinder->color));
	return (SUCCESS);
}

int	validate_store_cone(t_parsing *p, t_scene *s)
{
	if (p->position == 1)
		return (validate_and_store_coordinates(p->parameter,
				&s->last_cone->apex));
	if (p->position == 2)
		return (validate_and_store_vector(p->parameter, &s->last_cone->axis));
	if (p->position == 3)
	{
		if (ascii_to_double(p->parameter, &p->number) == ERROR)
			return (ERROR);
		if (p->number <= 0.0)
			return (ERROR);
		s->last_cone->diameter = p->number;
	}
	if (p->position == 4)
	{
		if (ascii_to_double(p->parameter, &p->number) == ERROR)
			return (ERROR);
		if (p->number <= 0.0)
			return (ERROR);
		s->last_cone->height = p->number;
	}
	if (p->position == 5)
		return (validate_and_store_color(p->parameter, &s->last_cone->color));
	return (SUCCESS);
}
