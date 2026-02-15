/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:47:41 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/15 20:33:09 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

static t_color apply_ambient(t_color obj, t_am_light ambient)
{
	t_color out;

	if (!ambient.exists)
		return obj;
	out.red   = obj.red   * ambient.ratio;
	out.green = obj.green * ambient.ratio;
	out.blue  = obj.blue  * ambient.ratio;
	return out;
}

static double	compute_diffuse(t_hit *hit, t_light light)
{
	t_coordinates	light_dir;
	double			diff;

	if (!light.exists)
		return (0);

	light_dir.x = light.coords.x - hit->point.x;
	light_dir.y = light.coords.y - hit->point.y;
	light_dir.z = light.coords.z - hit->point.z;
	light_dir = vec_normalize(light_dir);

	diff = vec_dot(hit->normal, light_dir);
	if (diff < 0)
		return (0);

	return (diff * light.brightness);
}

static t_color apply_diffuse(t_color obj, double diff)
{
	t_color out;

	out.red   = obj.red   * diff;
	out.green = obj.green * diff;
	out.blue  = obj.blue  * diff;

	out.red   = clamp(out.red);
	out.green = clamp(out.green);
	out.blue  = clamp(out.blue);

	return out;
}

static t_color	get_hit_color(t_hit *hit)
{
	t_color	out;

	out.red = 0;
	out.green = 0;
	out.blue = 0;
	if (!hit || !hit->obj)
		return (out);
	if (hit->type == OBJ_SPHERE)
		return (((t_sphere *)hit->obj)->color);
	if (hit->type == OBJ_PLANE)
		return (((t_plane *)hit->obj)->color);
	if (hit->type == OBJ_CYLINDER)
		return (((t_cylinder *)hit->obj)->color);
	return (out);
}

t_color	shade_hit(t_scene *scene, t_hit *hit)
{
	t_color	base;
	t_color	amb;
	t_color	dif;
	t_color	out;
	double	diff;

	base = get_hit_color(hit);
	amb = apply_ambient(base, scene->ambient);
	out = amb;
	if (!scene->light.exists)
		return (out);
	if (is_in_shadow(scene, hit))
		return (out);
	diff = compute_diffuse(hit, scene->light);
	dif = apply_diffuse(base, diff);

	out.red = clamp(amb.red + dif.red);
	out.green = clamp(amb.green + dif.green);
	out.blue = clamp(amb.blue + dif.blue);
	return (out);
}
