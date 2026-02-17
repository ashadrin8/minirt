/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 10:00:00 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/17 12:04:58 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_INTERNAL_H
# define RENDER_INTERNAL_H

# include "defines.h"
# include "vector_math.h"
# include "render.h"

typedef struct s_shadow_ctx
{
	t_ray			shadow;
	t_hit			tmp;
	t_coordinates	light_dir;
	double			closest;
	double			light_dist2;
	double			traveled;
}	t_shadow_ctx;

typedef struct s_mlx_context
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
	size_t		width;
	size_t		height;
}	t_mlx_context;

typedef struct s_camera_calc
{
	double	aspect_ratio;
	double	vp_height;
	double	vp_width;
	t_vec3	lower_left_corner;
	double	focal_length;
	double	theta;
}	t_camera_calc;

// scene
void			render_scene(t_scene *scene, mlx_image_t *img);
t_ray			ray_create(t_scene *scene, mlx_image_t *img,
					size_t x, size_t y);

// objects
int				hit_closest_sphere(t_ray ray, t_sphere *spheres,
					t_hit *hit, double *closest);
int				hit_closest_plane(t_ray ray, t_plane *planes,
					t_hit *hit, double *closest);
int				hit_closest_cylinder(t_ray ray, t_cylinder *cylinders,
					t_hit *hit, double *closest);
int				hit_closest_cone(t_ray ray, t_cone *cones,
					t_hit *hit, double *closest);

// lights
t_color			shade_hit(t_scene *scene, t_hit *hit);
int				is_in_shadow(t_scene *scene, t_hit *hit);

// camera
void			camera_prepare_orientation(t_camera *cam, mlx_image_t *img);
void			handle_camera_rotation(mlx_key_data_t keydata,
					t_scene *scene);

// utils
uint32_t		rgba(int r, int g, int b, int a);
int				clamp(int value);
t_coordinates	ray_at(t_ray ray, double t);

#endif
