#ifndef RENDER_INTERNAL_H
# define RENDER_INTERNAL_H

# include "defines.h"
# include "vector_math.h"

#define INF 1e30
#define EPS 1e-4
typedef enum e_obj_type
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE
}	t_obj_type;

typedef struct s_ray
{
	t_coordinates origin;
	t_coordinates direction;
}	t_ray;

typedef struct s_hit
{
	t_obj_type		type;
	void			*obj;
	t_coordinates	point;
	t_coordinates	normal;
	double			t;
}	t_hit;


//mlx
typedef struct	s_mlx_context {
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		*scene;
	size_t		width;
	size_t		height;
}	t_mlx_context;

// scene
void			render_scene(t_scene *scene, mlx_image_t *img);
// t_ray		make_camera_ray(t_scene *scene, mlx_image_t *img, size_t x, size_t y);

// objects
int				hit_closest_object(t_ray ray, t_scene *scene, t_hit *hit);
int 			hit_closest_sphere(t_ray ray, t_sphere *spheres, t_hit *hit, double *closest);
int				hit_closest_plane(t_ray ray, t_plane *planes, t_hit *hit, double *closest);
int				hit_closest_cylinder(t_ray ray, t_cylinder *cylinders, t_hit *hit, double *closest);
int				hit_closest_cone(t_ray ray, t_cone *cones, t_hit *hit, double *closest);

// lights
t_color			shade_hit(t_scene *scene, t_hit *hit);
int				is_in_shadow(t_scene *scene, t_hit *hit);	

//camera
void			camera_prepare_orientation(t_camera	*cam, mlx_image_t *img);
t_ray			ray_create(t_scene *scene, mlx_image_t *img, size_t x, size_t y);

// utils
uint32_t		rgba(int r, int g, int b, int a);
int 			clamp(int value);
t_coordinates	ray_at(t_ray ray, double t);

#endif
