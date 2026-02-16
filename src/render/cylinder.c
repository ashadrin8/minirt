/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:11:36 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/17 00:00:21 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

static int	hit_cap(t_ray ray, t_cylinder *cy, int top, double *t_out)
{
	t_coordinates	cc;
	t_coordinates	v;
	t_coordinates	axis;
	double			denom;
	double			t;

	axis = vec_normalize(cy->vector);
	if (top)
		cc = vec_add(cy->center, vec_scale(axis, cy->height * 0.5));
	else
		cc = vec_subtract(cy->center, vec_scale(axis, cy->height * 0.5));
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
