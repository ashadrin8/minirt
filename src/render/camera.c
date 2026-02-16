/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:33:21 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/16 23:09:02 by ashadrin         ###   ########.fr       */
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
	ray.direction = vec_normalize(vec_subtract(point_on_plane,
				scene->camera.coords));
	return (ray);
}

void	view_plane_calc(t_camera *cam, mlx_image_t *img)
{
	t_camera_calc	c;

	c.focal_length = 1.0;
	c.aspect_ratio = (double)img->width / (double)img->height;
	c.theta = cam->view * M_PI / 180.0;
	c.vp_height = 2 * tan(c.theta / 2);
	c.vp_width = c.aspect_ratio * c.vp_height;
	cam->vertical = vec_scale(cam->up, c.vp_height);
	cam->horizontal = vec_scale(cam->right, c.vp_width);
	c.lower_left_corner = vec_subtract(vec_subtract(vec_add(cam->coords,
					vec_scale(cam->forward, c.focal_length)),
				vec_scale(cam->horizontal, 0.5)),
			vec_scale(cam->vertical, 0.5));
	cam->llc = c.lower_left_corner;
}

void	camera_prepare_orientation(t_camera	*cam, mlx_image_t *img)
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
	view_plane_calc(cam, img);
}

void	handle_camera_rotation(mlx_key_data_t keydata, t_scene *scene)
{
	if (keydata.key == MLX_KEY_UP)
		scene->camera.forward = vec_rotate(scene->camera.forward,
				scene->camera.right, 0.05);
	else if (keydata.key == MLX_KEY_DOWN)
		scene->camera.forward = vec_rotate(scene->camera.forward,
				scene->camera.right, -0.05);
	else if (keydata.key == MLX_KEY_RIGHT)
		scene->camera.forward = vec_rotate(scene->camera.forward,
				scene->camera.up, 0.05);
	else if (keydata.key == MLX_KEY_LEFT)
		scene->camera.forward = vec_rotate(scene->camera.forward,
				scene->camera.up, -0.05);
}
