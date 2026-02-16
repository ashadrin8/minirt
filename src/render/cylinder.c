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

static int	valid_side_hit(t_ray ray, t_cylinder *cy, t_coordinates axis,
	double t)
{
	double	h;
	double	half_h;

	if (t <= EPS)
		return (0);
	h = vec_dot(vec_subtract(vec_add(ray.origin, vec_scale(ray.direction, t)),
				cy->center), axis);
	half_h = cy->height * 0.5;
	return (h >= -half_h - EPS && h <= half_h + EPS);
}

static int	hit_cylinder_side(t_ray ray, t_cylinder *cy, double *t)
{
	t_coordinates	d_perp;
	t_coordinates	oc_perp;
	t_coordinates	oc;
	t_coordinates	axis;
	double			a;
	double			b;
	double			c;
	double			disc;
	double			sqrt_disc;
	double			t0;
	double			t1;

	axis = vec_normalize(cy->vector);
	oc = vec_subtract(ray.origin, cy->center);
	d_perp = vec_subtract(ray.direction,
			vec_scale(axis, vec_dot(ray.direction, axis)));
	oc_perp = vec_subtract(oc,
			vec_scale(axis, vec_dot(oc, axis)));
	a = vec_dot(d_perp, d_perp);
	b = 2.0 * vec_dot(d_perp, oc_perp);
	c = vec_dot(oc_perp, oc_perp) - (cy->diameter * cy->diameter / 4.0);
	if (fabs(a) < EPS)
		return (0);
	disc = b * b - 4.0 * a * c;
	if (disc < 0.0)
		return (0);
	sqrt_disc = sqrt(disc);
	t0 = (-b - sqrt_disc) / (2.0 * a);
	t1 = (-b + sqrt_disc) / (2.0 * a);
	if (t0 > t1)
	{
		*t = t0;
		t0 = t1;
		t1 = *t;
	}
	if (valid_side_hit(ray, cy, axis, t0))
	{
		*t = t0;
		return (1);
	}
	if (valid_side_hit(ray, cy, axis, t1))
	{
		*t = t1;
		return (1);
	}
	return (0);
}

static int	hit_cap(t_ray ray, t_cylinder *cy, int top, double *t_out)
{
	t_coordinates	cc;
	t_coordinates	v;
	t_coordinates	axis;
	double			denom;
	double			t;
	double			half_h;

	axis = vec_normalize(cy->vector);
	half_h = cy->height * 0.5;
	if (top)
		cc = vec_add(cy->center, vec_scale(axis, half_h));
	else
		cc = vec_subtract(cy->center, vec_scale(axis, half_h));
	denom = vec_dot(ray.direction, axis);
	if (fabs(denom) < EPS)
		return (0);
	t = vec_dot(vec_subtract(cc, ray.origin), axis) / denom;
	if (t <= EPS)
		return (0);
	v = vec_subtract(vec_add(ray.origin, vec_scale(ray.direction, t)), cc);
	v = vec_subtract(v, vec_scale(axis, vec_dot(v, axis)));
	if (vec_dot(v, v) > (cy->diameter / 2.0) * (cy->diameter / 2.0) + EPS)
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
	double		t_side;

	while (cyls)
	{
		t_side = INF;
		hit_cylinder_side(ray, cyls, &t_side);
		hit_caps(ray, cyls, &hits.cap0, &hits.cap1);
		hits.closest_t = *closest;
		if (find_closest_hit(t_side, hits.cap0, hits.cap1,
				&hits.closest_t))
		{
			*closest = hits.closest_t;
			update_hit(hit, ray, cyls, hits);
		}
		cyls = cyls->next;
	}
	return (hit->type != OBJ_NONE);
}
