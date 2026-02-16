/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_side.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:10:00 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/17 00:10:00 by chiarakappe      ###   ########.fr       */
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

static void	setup_side_eq(t_ray ray, t_cylinder *cy, t_side_eq *eq)
{
	t_coordinates	oc;

	eq->axis = vec_normalize(cy->vector);
	oc = vec_subtract(ray.origin, cy->center);
	eq->d_perp = vec_subtract(ray.direction,
			vec_scale(eq->axis, vec_dot(ray.direction, eq->axis)));
	eq->oc_perp = vec_subtract(oc, vec_scale(eq->axis,
				vec_dot(oc, eq->axis)));
	eq->a = vec_dot(eq->d_perp, eq->d_perp);
	eq->b = 2.0 * vec_dot(eq->d_perp, eq->oc_perp);
	eq->c = vec_dot(eq->oc_perp, eq->oc_perp) - (cy->diameter
			* cy->diameter / 4.0);
}

static int	solve_side_eq(t_side_eq *eq)
{
	double	disc;
	double	sqrt_disc;

	if (fabs(eq->a) < EPS)
		return (0);
	disc = eq->b * eq->b - 4.0 * eq->a * eq->c;
	if (disc < 0.0)
		return (0);
	sqrt_disc = sqrt(disc);
	eq->t0 = (-eq->b - sqrt_disc) / (2.0 * eq->a);
	eq->t1 = (-eq->b + sqrt_disc) / (2.0 * eq->a);
	return (1);
}

static void	order_roots(double *t0, double *t1)
{
	double	tmp;

	if (*t0 > *t1)
	{
		tmp = *t0;
		*t0 = *t1;
		*t1 = tmp;
	}
}

int	hit_cylinder_side(t_ray ray, t_cylinder *cy, double *t)
{
	t_side_eq	eq;

	setup_side_eq(ray, cy, &eq);
	if (!solve_side_eq(&eq))
		return (0);
	order_roots(&eq.t0, &eq.t1);
	if (valid_side_hit(ray, cy, eq.axis, eq.t0))
	{
		*t = eq.t0;
		return (1);
	}
	if (valid_side_hit(ray, cy, eq.axis, eq.t1))
	{
		*t = eq.t1;
		return (1);
	}
	return (0);
}
