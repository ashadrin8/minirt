/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 18:57:15 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/26 19:34:54 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

static int	hit_plane(t_ray ray, t_plane *pl, double *t_out)
{
	double denom;
	double t;
	t_coordinates p0o;

	denom = dot(ray.direction, pl->vector);
	if (fabs(denom) < EPS)
		return (0);

	p0o.x = pl->point.x - ray.origin.x;
	p0o.y = pl->point.y - ray.origin.y;
	p0o.z = pl->point.z - ray.origin.z;

	t = dot(p0o, pl->vector) / denom;
	if (t <= EPS)
		return (0);

	*t_out = t;
	return (1);
}

int	hit_closest_plane(t_ray ray, t_plane *planes, t_hit *hit, double *closest)
{
	double t;

	while (planes)
	{
		if (hit_plane(ray, planes, &t) && t < *closest)
		{
			*closest = t;
			hit->type = OBJ_PLANE;
			hit->obj = planes;
			hit->t = t;
			hit->point.x = ray.origin.x + t * ray.direction.x;
			hit->point.y = ray.origin.y + t * ray.direction.y;
			hit->point.z = ray.origin.z + t * ray.direction.z;
			hit->normal = planes->vector;
			normalize(&hit->normal);
			if (dot(hit->normal, ray.direction) > 0)
			{
				hit->normal.x *= -1;
				hit->normal.y *= -1;
				hit->normal.z *= -1;
			}
		}
		planes = planes->next;
	}
	return (hit->type != OBJ_NONE);
}

