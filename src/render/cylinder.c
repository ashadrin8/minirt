/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:11:36 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/27 20:00:21 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

static int	hit_cylinder_side(t_ray ray, t_cylinder *cy, double *t)
{
	t_coordinates	d_perp;
	t_coordinates	oc_perp;
	t_coordinates	oc;
	double			height;
	double			h;

	oc = vec_subtract(cy->center, ray.origin);
	d_perp = vec_subtract(ray.direction,
			vec_scale(cy->vector, vec_dot(ray.direction, cy->vector)));
	oc_perp = vec_subtract(oc,
			vec_scale(cy->vector, vec_dot(oc, cy->vector)));
	if (!solve_quadratic(d_perp, oc_perp, cy->diameter / 2.0, t))
		return (0);
	height = vec_dot(cy->vector, cy->vector);
	oc = vec_add(ray.origin, vec_scale(ray.direction, *t));
	h = vec_dot(vec_subtract(oc, cy->center), cy->vector);
	return (h >= -EPS && h <= height + EPS);
}

static int	hit_cap(t_ray ray, t_cylinder *cy, int top, double *t_out)
{
	t_coordinates	cc;
	t_coordinates	v;
	double			denom;
	double			t;

	if (top)
		cc = vec_add(cy->center, cy->vector);
	else
		cc = cy->center;
	denom = vec_dot(ray.direction, cy->vector);
	if (fabs(denom) < EPS)
		return (0);
	t = vec_dot(vec_subtract(cc, ray.origin), cy->vector) / denom;
	if (t <= EPS)
		return (0);
	v = vec_subtract(vec_add(ray.origin, vec_scale(ray.direction, t)), cc);
	if (vec_dot(v, v) > (cy->diameter / 2.0) * (cy->diameter / 2.0))
		return (0);
	*t_out = t;
	return (1);
}

static void	hit_caps(t_ray r, t_cylinder *cy, t_cap_hit *cap0,
	t_cap_hit *cap1)
{
	double	t;

	cap0->hit = 0;
	cap0->t = INF;
	if (hit_cap(r, cy, 0, &t))
		set_cap_hit(cap0, 0, t);
	cap1->hit = 0;
	cap1->t = INF;
	if (hit_cap(r, cy, 1, &t))
		set_cap_hit(cap1, 1, t);
}

int	hit_closest_cylinder(t_ray ray, t_cylinder *cyls,
	t_hit *hit, double *closest)
{
	t_cyl_hits	hits;

	while (cyls)
	{
		hit_cylinder_side(ray, cyls, &hits.closest_t);
		hit_caps(ray, cyls, &hits.cap0, &hits.cap1);
		hits.closest_t = *closest;
		if (find_closest_hit(hits.closest_t, hits.cap0, hits.cap1,
				&hits.closest_t))
		{
			*closest = hits.closest_t;
			update_hit(hit, ray, cyls, hits);
		}
		cyls = cyls->next;
	}
	return (hit->type != OBJ_NONE);
}
