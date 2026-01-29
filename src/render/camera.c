/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:33:21 by ashadrin          #+#    #+#             */
/*   Updated: 2026/01/29 19:24:42 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"
#include "defines.h"
#include "render_internal.h"

t_ray	ray_create(t_scene *scene, mlx_image_t *img, size_t x, size_t y)
{
	t_ray	ray;
	double	u;
	double	v;
	t_vec3	point_on_plane;
	
	ray.origin = scene->camera.coords;
	u = (double)x / (img->width - 1);
	v = (double)y / (img->height - 1);
	point_on_plane = vec_add(vec_add(scene->camera.llc, 
		vec_scale(scene->camera.horizontal, u)), 
		vec_scale(scene->camera.vertical, v));
	ray.direction = vec_normalize(vec_subtract(point_on_plane, scene->camera.coords));
	
	return (ray);
}

void	view_plane_calc(t_camera *cam)
{
	double	aspect_ratio;
	double	vp_height;
	double	vp_width;
	t_vec3	lower_left_corner;
	double	focal_length;

	focal_length = 1.0;
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	vp_height = 2 * tan(cam->view / 2);
	vp_width = aspect_ratio * vp_height;
	cam->vertical = vec_scale(cam->up, vp_height);
	cam->horizontal = vec_scale(cam->right, vp_width);
	lower_left_corner = vec_subtract(vec_subtract(vec_add(cam->coords, vec_scale(cam->forward, focal_length)), 
					vec_scale(cam->horizontal, 0.5)), vec_scale(cam->vertical, 0.5));
	cam->llc = lower_left_corner;
}

void	camera_prepare_orientation(t_camera	*cam)
{
	t_vec3	world_up;
	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;

	world_up = (t_vec3){0.0, 1.0, 0.0};
	if (fabs(vec_dot(cam->forward, world_up)) > 0.99)
		world_up = (t_vec3){0.0, 0.0, 1.0};
	forward = vec_normalize(cam->forward);
	cam->forward = forward;
	right = vec_normalize(vec_cross(forward, world_up));
	cam->right = right;
	up = vec_normalize(vec_cross(forward, right));
	cam->up = up;
	view_plane_calc(cam);
}
