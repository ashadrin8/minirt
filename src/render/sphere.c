/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:44:56 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/04 16:04:31 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

/* intersect = discriminant

meaning:
< 0 → no intersection
= 0 → tangent
> 0 → two intersection points */


/* static int hit_any_sphere(t_ray ray, t_sphere *spheres)
{
	while (spheres)
	{
		if (hit_sphere(ray, spheres))
			return (1);
		spheres = spheres->next;
	}
	return (0);
} */

static int hit_sphere(t_ray ray, t_sphere *sphere, double *t_out)
{
	t_coordinates	oc;
	double			a;
	double			b;
	double			c;
	double			intersect;
	double			t;
//	double			radius;

	// radius = sphere->diameter / 2.0;
	// oc = origin - center
	oc.x = ray.origin.x - sphere->center.x;
	oc.y = ray.origin.y - sphere->center.y;
	oc.z = ray.origin.z - sphere->center.z;

	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(oc, ray.direction);
	c = dot(oc, oc) - (sphere->diameter * sphere->diameter / 4.0);

	// intersection math
	intersect = b * b - 4 * a * c;
	if (intersect < 0)
		return (0);
	t = (-b - sqrt(intersect)) / (2 * a);
	if (t <= 0)
		return (0);
	*t_out = t;
	return (1);
}


/* Finds the closest intersected sphere
Stores a pointer to that exact sphere in hit_sphere */

int hit_closest_sphere(t_ray ray, t_sphere *spheres, t_hit *hit, double *closest)
{
	double	t;
	double	closest_t;
	int		updated;
	t_sphere	*sphere;

	closest_t = *closest;
	updated = 0;
	while (spheres)
	{
		if (hit_sphere(ray, spheres, &t) && t < closest_t)
		{
			closest_t = t;
			hit->type = OBJ_SPHERE;
			hit->obj = spheres;
			hit->t = t;
			updated = 1;
		}
		spheres = spheres->next;
	}
	if (!updated)
		return (0);
	
	*closest = closest_t;
	
	// hit point
	hit->point.x = ray.origin.x + hit->t * ray.direction.x;
	hit->point.y = ray.origin.y + hit->t * ray.direction.y;
	hit->point.z = ray.origin.z + hit->t * ray.direction.z;
	
	// normal
	sphere = (t_sphere *)hit->obj;
	hit->normal.x = hit->point.x - sphere->center.x;
	hit->normal.y = hit->point.y - sphere->center.y;
	hit->normal.z = hit->point.z - sphere->center.z;
	
	normalize(&hit->normal);
	return (1);
}
