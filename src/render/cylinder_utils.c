/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:11:36 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/27 20:00:21 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

int	solve_quadratic(t_coordinates d, t_coordinates oc,
	double r, double *t)
{
	double	a;
	double	disc;

	a = vec_dot(d, d);
	if (fabs(a) < EPS)
		return (0);
	disc = 4.0 * vec_dot(d, oc) * vec_dot(d, oc)
		- 4.0 * a * (vec_dot(oc, oc) - r * r);
	if (disc < 0)
		return (0);
	disc = sqrt(disc);
	*t = ((-2.0 * vec_dot(d, oc) - disc) / (2.0 * a));
	if (*t <= EPS)
		*t = ((-2.0 * vec_dot(d, oc) + disc) / (2.0 * a));
	return (*t > EPS);
}

t_coordinates	compute_side_normal(t_ray r, t_cylinder *cy, double t)
{
	t_coordinates	p;
	t_coordinates	proj;

	p = vec_add(r.origin, vec_scale(r.direction, t));
	proj = vec_add(cy->center, vec_scale(cy->vector,
				vec_dot(vec_subtract(p, cy->center), cy->vector)));
	return (vec_normalize(vec_subtract(p, proj)));
}

void	set_cap_hit(t_cap_hit *cap, int top, double t)
{
	(void)top;
	cap->hit = 1;
	cap->t = t;
}

int	find_closest_hit(double t_side, t_cap_hit cap0,
	t_cap_hit cap1, double *closest_t)
{
	double	t;

	t = INF;
	if (t_side < INF)
		t = t_side;
	if (cap0.hit && cap0.t < t)
		t = cap0.t;
	if (cap1.hit && cap1.t < t)
		t = cap1.t;
	if (t != INF && t < *closest_t)
	{
		*closest_t = t;
		return (1);
	}
	return (0);
}

void	update_hit(t_hit *hit, t_ray ray, t_cylinder *cy, t_cyl_hits hits)
{
	t_coordinates	normal;

	hit->type = OBJ_CYLINDER;
	hit->obj = cy;
	hit->t = hits.closest_t;
	hit->point = vec_add(ray.origin, vec_scale(ray.direction, hits.closest_t));
	if (hits.cap0.hit && hits.closest_t == hits.cap0.t)
		hit->normal = vec_scale(cy->vector, -1.0);
	else if (hits.cap1.hit && hits.closest_t == hits.cap1.t)
		hit->normal = cy->vector;
	else
	{
		normal = compute_side_normal(ray, cy, hits.closest_t);
		if (vec_dot(normal, ray.direction) > 0)
			hit->normal = vec_scale(normal, -1.0);
		else
			hit->normal = normal;
	}
}
