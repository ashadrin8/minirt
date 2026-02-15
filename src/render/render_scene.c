/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:32:56 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/29 19:23:17 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"


int	hit_closest_object(t_ray ray, t_scene *scene, t_hit *hit)
{
	double closest;

	hit->type = OBJ_NONE;
	hit->obj = NULL;
	closest = INF;

	// spheres
	hit_closest_sphere(ray, scene->spheres, hit, &closest);

	// planes
	hit_closest_plane(ray, scene->planes, hit, &closest);

	// cylinders
	hit_closest_cylinder(ray, scene->cylinders, hit, &closest);

	return (hit->type != OBJ_NONE);
}

void	render_scene(t_scene *scene, mlx_image_t *img)
{
	size_t		x;
	size_t		y;
	t_ray		ray;
	t_hit		hit;
	t_color		color;

	camera_prepare_orientation(&scene->camera);
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			ray = ray_create(scene, img, x, y);
			if (hit_closest_object(ray, scene, &hit))
				color = shade_hit(scene, &hit);
			else
				color = (t_color){0, 0, 0};
			mlx_put_pixel(img, x, y,
				rgba(color.red, color.green, color.blue, 255));
		}
	}
}

