/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:32:56 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/26 14:54:06 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

/* normalize a vector means:
Scale it so its length (magnitude) is exactly 1. */

void normalize(t_coordinates *v)
{
	double len;

	len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (len == 0)
		return;
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

t_ray	make_camera_ray(t_scene *scene, mlx_image_t *img, size_t x, size_t y)
{
	t_ray	ray;
	double	u;
	double	v;

	ray.origin = scene->camera.coords;

	u = (2.0 * x / (img->width - 1)) - 1.0;
	v = 1.0 - (2.0 * y / (img->height - 1));

	ray.direction.x = u;
	ray.direction.y = v;
	ray.direction.z = 1.0;
	normalize(&ray.direction);

	return (ray);
}

void	render_scene(t_scene *scene, mlx_image_t *img)
{
	size_t		x;
	size_t		y;
	t_ray		ray;
	t_hit		hit;
	t_color		color;

	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			ray = make_camera_ray(scene, img, x, y);
			if (hit_closest_sphere(ray, scene->spheres, &hit))
				color = shade_hit(scene, &hit);
			else
				color = (t_color){0, 0, 0};
			mlx_put_pixel(img, x, y,
				rgba(color.red, color.green, color.blue, 255));
		}
	}
}
