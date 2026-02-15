/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 20:12:34 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/30 22:58:41 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

int	is_in_shadow(t_scene *scene, t_hit *hit)
{
	t_ray			shadow;
	t_hit			tmp;
	t_coordinates	light_dir;
	double			closest;
	double			light_dist2;

	if (!scene->light.exists)
		return (0);
	light_dir = vec_subtract(scene->light.coords, hit->point);
	light_dist2 = vec_dot(light_dir, light_dir);
	light_dir = vec_normalize(light_dir);
	shadow.origin = vec_add(hit->point, vec_scale(hit->normal, (EPS * 10)));
	shadow.direction = light_dir;
	
	tmp.type = OBJ_NONE;
	tmp.obj = NULL;
	closest = INF;
	hit_closest_sphere(shadow, scene->spheres, &tmp, &closest);
	hit_closest_plane(shadow, scene->planes, &tmp, &closest);
	hit_closest_cylinder(shadow, scene->cylinders, &tmp, &closest);
	
	if (tmp.type == OBJ_NONE)
		return (0);
	return ((closest * closest) < light_dist2);
}
