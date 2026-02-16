/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 10:00:00 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/16 10:00:00 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_INTERNAL_H
# define RENDER_INTERNAL_H

# include "defines.h"
# include "vector_math.h"

# define INF 1e30
# define EPS 1e-4

typedef struct s_cap_hit
{
	int		hit;
	double	t;
}	t_cap_hit;

typedef struct s_cyl_hits
{
	t_cap_hit	cap0;
	t_cap_hit	cap1;
	double		closest_t;
}	t_cyl_hits;

typedef enum e_obj_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_ray
{
	t_coordinates	origin;
	t_coordinates	direction;
}	t_ray;

typedef struct s_hit
{
	t_obj_type		type;
	void			*obj;
	t_coordinates	point;
	t_coordinates	normal;
	double			t;
}	t_hit;

typedef struct s_mlx_context
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
	size_t		width;
	size_t		height;
}	t_mlx_context;

// scene
void			render_scene(t_scene *scene, mlx_image_t *img);
t_ray			ray_create(t_scene *scene, mlx_image_t *img,
				size_t x, size_t y);

// objects
int				hit_closest_object(t_ray ray, t_scene *scene, t_hit *hit);
int				hit_closest_sphere(t_ray ray, t_sphere *spheres,
				t_hit *hit, double *closest);
int				hit_closest_plane(t_ray ray, t_plane *planes,
				t_hit *hit, double *closest);
int				hit_closest_cylinder(t_ray ray, t_cylinder *cylinders,
				t_hit *hit, double *closest);
int				solve_quadratic(t_coordinates d, t_coordinates oc,
				double r, double *t);
t_coordinates	compute_side_normal(t_ray r, t_cylinder *cy, double t);
void			set_cap_hit(t_cap_hit *cap, int top, double t);
int				find_closest_hit(double t_side, t_cap_hit cap0,
				t_cap_hit cap1, double *closest_t);
void			update_hit(t_hit *hit, t_ray ray, t_cylinder *cy,
				t_cyl_hits hits);

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

#endif
