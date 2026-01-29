/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 15:10:42 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/27 18:43:09 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

t_coordinates	vec_sub(t_coordinates a, t_coordinates b)
{
	return ((t_coordinates){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_coordinates	vec_add(t_coordinates a, t_coordinates b)
{
	return ((t_coordinates){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_coordinates	vec_scale(t_coordinates v, double s)
{
	return ((t_coordinates){v.x * s, v.y * s, v.z * s});
}

t_coordinates	vec_normalize(t_coordinates v)
{
	normalize(&v);
	return (v);
}

t_coordinates	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}
