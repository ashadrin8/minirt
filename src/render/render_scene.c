/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:32:56 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/17 19:01:41 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"


/* intersect = discriminant

meaning:
< 0 → no intersection
= 0 → tangent
> 0 → two intersection points */


/* static int hit_any_sphere(t_ray ray, t_sphere *spheres)
{
	while (spheres)
	{
		if (hit_sphere(ray, spheres))
			return (1);
		spheres = spheres->next;
	}
	return (0);
} */


static int hit_sphere(t_ray ray, t_sphere *sphere, double *t_out)
{
	t_coordinates	oc;
	double			a;
	double			b;
	double			c;
	double			intersect;
	double			t;
//	double			radius;

	// radius = sphere->diameter / 2.0;
	// oc = origin - center
	oc.x = ray.origin.x - sphere->center.x;
	oc.y = ray.origin.y - sphere->center.y;
	oc.z = ray.origin.z - sphere->center.z;

	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(oc, ray.direction);
	c = dot(oc, oc) - (sphere->diameter * sphere->diameter / 4.0);

	// intersection math
	intersect = b * b - 4 * a * c;
	if (intersect < 0)
		return (0);
	t = (-b - sqrt(intersect)) / (2 * a);
	if (t <= 0)
		return (0);
	*t_out = t;
	return (1);
}

static int hit_closest_sphere(t_ray ray, t_sphere *spheres, double *t_hit, t_sphere **hitted_sphere)
{
	double	t;
	double closest_t;
	int hit;

	// veeeeery high number (kinda infinte from our perspective)
	closest_t = 1e30;
	hit = 0;
	while (spheres)
	{
		if (hit_sphere(ray, spheres, &t) && t < closest_t)
		{
			closest_t = t;
			*hitted_sphere = spheres;
			hit = 1;
		}
		spheres = spheres->next;
	}
	if (hit)
		*t_hit = closest_t;
	return hit;
}

void	render_scene(t_scene *scene, mlx_image_t *img)
{
	size_t		x;
	size_t		y;
	t_ray		ray;
	double		t;
	t_sphere	*hit_sphere;

	t = 0;
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
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
			if (hit_closest_sphere(ray, scene->spheres, &t, &hit_sphere))
				mlx_put_pixel(img, x, y, rgba(255, 0, 0, 255));
			else
				mlx_put_pixel(img, x, y, rgba(0, 0, 0, 255));
		}
	}
}

