#ifndef RENDER_INTERNAL_H
# define RENDER_INTERNAL_H

# include "defines.h"

typedef struct s_ray
{
	t_coordinates origin;
	t_coordinates direction;
}	t_ray;

typedef struct s_hit
{
	t_sphere		*sphere;
	t_coordinates	point;
	t_coordinates	normal;
	double			t;
}	t_hit;


// scene
void		render_scene(t_scene *scene, mlx_image_t *img);
void 		normalize(t_coordinates *v);
int 		hit_closest_sphere(t_ray ray, t_sphere *spheres, t_hit *hit);

// lights
t_color		shade_hit(t_scene *scene, t_hit *hit);

// utils
uint32_t	rgba(int r, int g, int b, int a);
double 		dot(t_coordinates a, t_coordinates b);
int 		clamp(int value);

#endif