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

static void	cylinder_perp(t_ray ray, t_cylinder *cy, t_coordinates axis,
	t_coordinates *d_perp, t_coordinates *oc_perp)
{
	t_coordinates	oc;
	double			d_dot;
	double			oc_dot;

	oc = vec_subtract(ray.origin, cy->center);
	d_dot = vec_dot(ray.direction, axis);
	oc_dot = vec_dot(oc, axis);
	*d_perp = vec_subtract(ray.direction, vec_scale(axis, d_dot));
	*oc_perp = vec_subtract(oc, vec_scale(axis, oc_dot));
}

static int	cylinder_quadratic(t_coordinates d, t_coordinates oc,
	double r, double *t)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t0;
	double	t1;
	
	a = vec_dot(d, d);
	if (fabs(a) < EPS)
		return (0);
	b = 2.0 * vec_dot(d, oc);
	c = vec_dot(oc, oc) - r * r;
	disc = b * b - 4.0 * a * c;
	if (disc < 0)
		return (0);
	disc = sqrt(disc);
	t0 = (-b - disc) / (2.0 * a);
	t1 = (-b + disc) / (2.0 * a);
	if (t0 > EPS && (t0 < t1 || t1 <= EPS))
		*t = t0;
	else if (t1 > EPS)
		*t = t1;
	else
		return (0);
	return (1);
}

static int	cylinder_height_check(t_ray ray, t_cylinder *cy, 
	t_coordinates axis,double t)
{
	double	m;

	m = vec_dot(vec_subtract(vec_add(ray.origin, vec_scale(ray.direction, t)),
				cy->center), axis);
	return (m >= -cy->height / 2.0 && m <= cy->height / 2.0);
}

static int	hit_cylinder_side(t_ray ray, t_cylinder *cy, t_coordinates axis, double *t_out)
{
	t_coordinates	d_perp;
	t_coordinates	oc_perp;
	double			t;
	double			r;

	r = cy->diameter / 2.0;
	cylinder_perp(ray, cy, axis, &d_perp, &oc_perp);
	if (!cylinder_quadratic(d_perp, oc_perp, r, &t))
		return (0);
	if (!cylinder_height_check(ray, cy, axis, t))
		return (0);
	*t_out = t;
	return (1);
}


static t_coordinates	cap_center(t_cylinder *cy, t_coordinates a, int top)
{
	if (top)
		return (vec_add(cy->center, vec_scale(a, cy->height / 2.0)));
	return (vec_subtract(cy->center, vec_scale(a, cy->height / 2.0)));
}


static int	hit_cylinder_cap(t_ray ray, t_cylinder *cy, t_coordinates axis,
	int top, double *t_out)
{
	t_coordinates	cc;
	t_coordinates	p;
	t_coordinates	v;
	double			denom;
	double			t;
	double			r;

	r = cy->diameter / 2.0;
	cc = cap_center(cy, axis, top);
	denom = vec_dot(ray.direction, axis);
	if (fabs(denom) < EPS)
		return (0);
	t = vec_dot(vec_subtract(cc, ray.origin), axis) / denom;
	if (t <= EPS)
		return (0);
	p = vec_add(ray.origin, vec_scale(ray.direction, t));
	v = vec_subtract(p, cc);
	if (vec_dot(v, v) > r * r)
		return (0);
	*t_out = t;
	return (1);
}



static t_coordinates	cylinder_side_normal(t_ray ray, t_cylinder *cy, 
	t_coordinates axis, double t)
{
	t_coordinates	p;
	t_coordinates	proj;

	p = vec_add(ray.origin, vec_scale(ray.direction, t));
	proj = vec_add(cy->center, vec_scale(axis,
				vec_dot(vec_subtract(p, cy->center), axis)));
	return (vec_normalize(vec_subtract(p, proj)));
}

static int	hit_cylinder(t_ray ray, t_cylinder *cy,
	double *t_out, t_coordinates *n_out)
{
	t_coordinates	axis;
	double			t_side;
	double			t_cap0;
	double			t_cap1;
	double			t;
	int				hit_cap0;
	int				hit_cap1;

	axis = vec_normalize(cy->vector);
	t = INF;
	t_cap0 = INF;
	t_cap1 = INF;
	hit_cap0 = 0;
	hit_cap1 = 0;
	if (hit_cylinder_side(ray, cy, axis, &t_side) && t_side < t)
		t = t_side;
	hit_cap0 = hit_cylinder_cap(ray, cy, axis, 0, &t_cap0);
	if (hit_cap0 && t_cap0 < t)
		t = t_cap0;
	hit_cap1 = hit_cylinder_cap(ray, cy, axis, 1, &t_cap1);
	if (hit_cap1 && t_cap1 < t)
		t = t_cap1;
	if (t == INF)
		return (0);
	*t_out = t;
	if (hit_cap0 && t == t_cap0)
		*n_out = vec_scale(axis, -1.0);
	else if (hit_cap1 && t == t_cap1)
		*n_out = axis;
	else
		*n_out = cylinder_side_normal(ray, cy, axis, t);
	return (1);
}

int	hit_closest_cylinder(t_ray ray, t_cylinder *cyls,
	t_hit *hit, double *closest)
{
	double			t;
	t_coordinates	n;

	while (cyls)
	{
		if (hit_cylinder(ray, cyls, &t, &n) && t < *closest)
		{
			*closest = t;
			hit->type = OBJ_CYLINDER;
			hit->obj = cyls;
			hit->t = t;
			hit->point = vec_add(ray.origin, vec_scale(ray.direction, t));
			hit->normal = n;
			if (vec_dot(hit->normal, ray.direction) > 0)
				hit->normal = vec_scale(hit->normal, -1.0);
		}
		cyls = cyls->next;
	}
	return (hit->type != OBJ_NONE);
}
