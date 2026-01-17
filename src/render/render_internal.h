#ifndef RENDER_INTERNAL_H
# define RENDER_INTERNAL_H

# include "defines.h"

typedef struct s_ray
{
	t_coordinates origin;
	t_coordinates direction;
}	t_ray;


void		render_scene(t_scene *scene, mlx_image_t *img);

// utils
uint32_t	rgba(int r, int g, int b, int a);
double 		dot(t_coordinates a, t_coordinates b);


#endif