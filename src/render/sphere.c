/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:44:56 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/26 18:55:46 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

static int	hit_sphere(t_ray ray, t_sphere *sphere, double *t_out)
{
	t_coordinates	oc;
	double			a;
	double			b;
	double			c;
	double			intersect;

	oc.x = ray.origin.x - sphere->center.x;
	oc.y = ray.origin.y - sphere->center.y;
	oc.z = ray.origin.z - sphere->center.z;
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0 * vec_dot(oc, ray.direction);
	c = vec_dot(oc, oc) - (sphere->diameter * sphere->diameter / 4.0);
	intersect = b * b - 4 * a * c;
	if (intersect < 0)
		return (0);
	*t_out = (-b - sqrt(intersect)) / (2 * a);
	if (*t_out <= 0)
		return (0);
	return (1);
}

static void	compute_hit_data(t_hit *hit, t_ray ray, t_sphere *sphere)
{
	hit->point.x = ray.origin.x + hit->t * ray.direction.x;
	hit->point.y = ray.origin.y + hit->t * ray.direction.y;
	hit->point.z = ray.origin.z + hit->t * ray.direction.z;
	hit->normal.x = hit->point.x - sphere->center.x;
	hit->normal.y = hit->point.y - sphere->center.y;
	hit->normal.z = hit->point.z - sphere->center.z;
	hit->normal = vec_normalize(hit->normal);
}

int	hit_closest_sphere(t_ray ray, t_sphere *spheres, t_hit *hit,
	double *closest)
{
	double		t;
	double		closest_t;
	int			updated;

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
	compute_hit_data(hit, ray, (t_sphere *)hit->obj);
	return (1);
}
