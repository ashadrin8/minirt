/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 20:12:34 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/16 23:03:04 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

static void	cast_shadow_ray(t_scene *scene, t_ray shadow, t_hit *tmp,
	double *closest)
{
	tmp->type = OBJ_NONE;
	tmp->obj = NULL;
	*closest = INF;
	hit_closest_sphere(shadow, scene->spheres, tmp, closest);
	hit_closest_plane(shadow, scene->planes, tmp, closest);
	hit_closest_cylinder(shadow, scene->cylinders, tmp, closest);
}

static void	setup_shadow_ctx(t_scene *scene, t_hit *hit, t_shadow_ctx *ctx)
{
	t_coordinates	bias_dir;

	ctx->light_dir = vec_subtract(scene->light.coords, hit->point);
	ctx->light_dist2 = vec_dot(ctx->light_dir, ctx->light_dir);
	ctx->light_dir = vec_normalize(ctx->light_dir);
	bias_dir = hit->normal;
	if (vec_dot(bias_dir, ctx->light_dir) < 0.0)
		bias_dir = vec_scale(bias_dir, -1.0);
	ctx->shadow.origin = vec_add(hit->point, vec_scale(bias_dir, (EPS * 10)));
	ctx->shadow.direction = ctx->light_dir;
	ctx->traveled = 0.0;
	cast_shadow_ray(scene, ctx->shadow, &ctx->tmp, &ctx->closest);
}

static int	skip_self_shadows(t_scene *scene, t_hit *hit, t_shadow_ctx *ctx)
{
	int	attempt;

	attempt = 0;
	while (attempt < 16 && ctx->tmp.type != OBJ_NONE
		&& ctx->tmp.type == hit->type && ctx->tmp.obj == hit->obj)
	{
		if ((ctx->traveled + ctx->closest) * (ctx->traveled
				+ ctx->closest) >= ctx->light_dist2)
			return (0);
		ctx->traveled += ctx->closest + (EPS * 10);
		ctx->shadow.origin = vec_add(ctx->shadow.origin,
				vec_scale(ctx->light_dir, ctx->closest + (EPS * 20)));
		cast_shadow_ray(scene, ctx->shadow, &ctx->tmp, &ctx->closest);
		attempt++;
	}
	return (1);
}

static int	is_valid_shadow_hit(t_hit *hit, t_shadow_ctx *ctx)
{
	double	total_dist;

	if (ctx->tmp.type == OBJ_NONE)
		return (0);
	if (ctx->tmp.type == hit->type && ctx->tmp.obj == hit->obj)
		return (0);
	if (ctx->closest <= EPS * 30)
		return (0);
	total_dist = ctx->traveled + ctx->closest;
	return ((total_dist * total_dist) < ctx->light_dist2);
}

int	is_in_shadow(t_scene *scene, t_hit *hit)
{
	t_shadow_ctx	ctx;

	if (!scene->light.exists)
		return (0);
	setup_shadow_ctx(scene, hit, &ctx);
	if (!skip_self_shadows(scene, hit, &ctx))
		return (0);
	return (is_valid_shadow_hit(hit, &ctx));
}
