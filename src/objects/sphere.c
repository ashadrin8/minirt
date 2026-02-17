/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:44:56 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/17 12:07:43 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects_internal.h"

static void	setup_sphere_eq(t_ray ray, t_sphere *sphere, t_sphere_eq *eq)
{
	eq->oc.x = ray.origin.x - sphere->center.x;
	eq->oc.y = ray.origin.y - sphere->center.y;
	eq->oc.z = ray.origin.z - sphere->center.z;
	eq->a = vec_dot(ray.direction, ray.direction);
	eq->b = 2.0 * vec_dot(eq->oc, ray.direction);
	eq->c = vec_dot(eq->oc, eq->oc) - (sphere->diameter * sphere->diameter
			/ 4.0);
}

static int	solve_sphere_eq(t_sphere_eq *eq)
{
	double	sqrt_disc;

	eq->disc = eq->b * eq->b - 4.0 * eq->a * eq->c;
	if (eq->disc < 0.0)
		return (0);
	sqrt_disc = sqrt(eq->disc);
	eq->t0 = (-eq->b - sqrt_disc) / (2.0 * eq->a);
	eq->t1 = (-eq->b + sqrt_disc) / (2.0 * eq->a);
	return (1);
}

static int	hit_sphere(t_ray ray, t_sphere *sphere, double *t_out)
{
	t_sphere_eq	eq;

	setup_sphere_eq(ray, sphere, &eq);
	if (!solve_sphere_eq(&eq))
		return (0);
	if (eq.t0 > EPS)
		*t_out = eq.t0;
	else if (eq.t1 > EPS)
		*t_out = eq.t1;
	else
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
