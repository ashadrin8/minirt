/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:32:56 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/16 23:50:30 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

static int hit_sphere(t_ray ray, t_sphere *sp)
{
	t_coordinates oc;
	double a;
	double b;
	double c;
	double discriminant;

	// oc = origin - center
	oc.x = ray.origin.x - sp->center.x;
	oc.y = ray.origin.y - sp->center.y;
	oc.z = ray.origin.z - sp->center.z;

	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(oc, ray.direction);
	c = dot(oc, oc) - (sp->diameter * sp->diameter / 4.0);

	discriminant = b * b - 4 * a * c;

	return (discriminant >= 0);
}

static int hit_any_sphere(t_ray ray, t_sphere *spheres)
{
	while (spheres)
	{
		if (hit_sphere(ray, spheres))
			return (1);
		spheres = spheres->next;
	}
	return (0);
}

void	render_scene(t_scene *scene, mlx_image_t *img)
{
	size_t	x;
	size_t	y;
	t_ray	ray;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			// 1. Ray origin
			ray.origin = scene->camera.coords;

			// 2. Pixel → normalized screen space
			double u = (2.0 * x / (img->width - 1)) - 1.0;
			double v = 1.0 - (2.0 * y / (img->height - 1));

			// 3. Ray direction (temporary camera)
			ray.direction.x = u;
			ray.direction.y = v;
			ray.direction.z = 1.0;

			// 4. TEMPORARY DEBUG COLOR
			if (hit_any_sphere(ray, scene->spheres))
				mlx_put_pixel(img, x, y, rgba(255, 0, 0, 255));
			else
				mlx_put_pixel(img, x, y, rgba(0, 0, 0, 255));
			x++;
		}
		y++;
	}
}
