/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:47:41 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/26 14:48:49 by chiarakappe      ###   ########.fr       */
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
	normalize(&light_dir);

	diff = dot(hit->normal, light_dir);
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

t_color	shade_hit(t_scene *scene, t_hit *hit)
{
	t_color	color;
	double	diff;

	color = apply_ambient(hit->sphere->color, scene->ambient);
	diff = compute_diffuse(hit, scene->light);
	color = apply_diffuse(color, diff);
	return (color);
}
