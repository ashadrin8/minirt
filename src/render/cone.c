/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 18:58:42 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/16 14:43:28 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

int	hit_cone_base(t_ray ray, t_cone *cone, t_vec3 axis, double *t_out)
{
	t_coordinates	base_center;
	double			denom;
	double			t;
	t_coordinates	P;
	t_vec3			v;
	
	base_center = vec_add(cone->apex, vec_scale(axis, cone->height));
	denom = vec_dot(ray.direction, axis);
	if (fabs(denom) <= EPS)
		return (0);
	t = vec_dot(vec_subtract(base_center, ray.origin), axis) / denom;
	if (t <= EPS)
		return (0);
	P = vec_add(ray.origin, vec_scale(ray.direction, t));
	v = vec_subtract(P, base_center);
	if (vec_dot(v, v) > (cone->radius * cone->radius))
		return (0);
	*t_out = t;
	return (1);
}

int	estimate_ts(t_cone_hit *hit, double *t_out)
{
	if (hit->t0 < 0)
	{
		if (hit->t1 < 0)
			return (0);
		*t_out = hit->t1;
		return (1);
	}
	if (hit->t1 < 0)
	{
		*t_out = hit->t0;
		return (1);
	}   
	if (hit->t0 < hit->t1)
	{
		*t_out = hit->t0;
		return (1);
	}
	*t_out = hit->t1;
	return (1);
}

static int 	hit_cone_side(t_ray ray, t_cone *cone, t_coordinates axis, double *t_out)
{
	t_cone_hit  hit;
	double		m;

	hit.oc = vec_subtract(ray.origin, cone->apex);
	hit.m = vec_dot(ray.direction, axis);
	hit.n = vec_dot(hit.oc, axis);
	hit.A = vec_dot(ray.direction, ray.direction) - (1 + cone->slope) * hit.m * hit.m;
	hit.B = 2 * (vec_dot(ray.direction, hit.oc) - (1 + cone->slope) * hit.m * hit.n);
	hit.C = vec_dot(hit.oc, hit.oc) - (1 + cone->slope) * hit.n * hit.n;
	hit.discriminant = hit.B * hit.B - 4 * hit.A * hit.C;
	if (hit.discriminant < 0)
		return (0);
	hit.t0 = ((hit.B * -1) - sqrt(hit.discriminant)) / (2 * hit.A);
	hit.t1 = ((hit.B * -1) + sqrt(hit.discriminant)) / (2 * hit.A);
	if (estimate_ts(&hit, t_out))
	{
		hit.P = ray_at(ray, *t_out);
		m = vec_dot(vec_subtract(hit.P, cone->apex), axis);
		if (m < 0 || m > cone->height)
			return (0);
		return (1);
	}
    return (0);
}

t_coordinates	cone_side_normal(t_ray ray, t_cone *cone, t_coordinates axis, double t)
{
	t_coordinates	P;
	t_vec3			v;
	t_coordinates	proj;
	t_vec3			normal;

	P = ray_at(ray, t);
	v = vec_subtract(P, cone->apex);
	proj = vec_scale(axis, vec_dot(v, axis));
	normal = vec_subtract(v, proj);
	return (vec_normalize(normal));
}

static int	hit_cone(t_ray ray, t_cone *cone, double *t_out, t_coordinates *n_out)
{
	t_coordinates	axis;
	double			t_side;
	double			t_base;
	double			t;
	int				hit_base;

	axis = vec_normalize(cone->axis);
	t = INF;
	t_base = INF;
	hit_base = 0;
	cone->radius = cone->diameter / 2;
	cone->slope = (cone->radius / cone->height) * (cone->radius / cone->height);
	if (hit_cone_side(ray, cone, axis, &t_side) && t_side < t)
		t = t_side;
	hit_base = hit_cone_base(ray, cone, axis, &t_base);
	if (hit_base && t_base < t)
		t = t_base;
	if (t == INF)
		return (0);
	*t_out = t;
	if (hit_base && t == t_base)
		*n_out = axis;
	else
		*n_out = cone_side_normal(ray, cone, axis, t);
	return (1);
}

int	hit_closest_cone(t_ray ray, t_cone *cones, t_hit *hit, double *closest)
{
	double			t;
	t_coordinates	n;

	while (cones)
	{
		if (hit_cone(ray, cones, &t, &n) && t < *closest)
		{
			*closest = t;
			hit->type = OBJ_CONE;
			hit->obj = cones;
			hit->t = t;
			hit->point = ray_at(ray, t);
			hit->normal = n;
			if (vec_dot(hit->normal, ray.direction) > 0)
				hit->normal = vec_scale(hit->normal, -1.0);
		}
		cones = cones->next;
	}
	return (hit->type != OBJ_NONE);
}