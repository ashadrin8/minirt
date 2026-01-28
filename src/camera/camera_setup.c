#include "vector_math.h"
#include "defines.h"

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
	vp_height = 2 * tan(cam->fov / 2);
	vp_width = aspect_ratio * vp_height;
	cam->vertical = vec_scale(cam->up, vp_height);
	cam->horizontal = vec_scale(cam->right, vp_width);
	lower_left_corner = vec_subtract(vec_subtract(vec_add(cam->coords, vec_scale(cam->forward, focal_length)), 
					vec_scale(cam->horizontal, 0.5)), vec_scale(cam->vertical, 0.5));
	cam->llc = lower_left_corner;
}
