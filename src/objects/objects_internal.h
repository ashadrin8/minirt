/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:47:53 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/17 12:17:14 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_INTERNAL_H
# define OBJECTS_INTERNAL_H

# include "defines.h"
# include "vector_math.h"
# include "render.h"

typedef struct c_cone_hit
{
	t_vec3	oc;
	double	m;
	double	n;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t0;
	double	t1;
	t_vec3	p;
}	t_cone_hit;

typedef struct s_sphere_eq
{
	t_coordinates	oc;
	double			a;
	double			b;
	double			c;
	double			disc;
	double			t0;
	double			t1;
}	t_sphere_eq;

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

typedef struct s_side_eq
{
	t_coordinates	axis;
	t_coordinates	d_perp;
	t_coordinates	oc_perp;
	double			a;
	double			b;
	double			c;
	double			t0;
	double			t1;
}	t_side_eq;

int				hit_closest_object(t_ray ray, t_scene *scene, t_hit *hit);
int				hit_closest_sphere(t_ray ray, t_sphere *spheres,
					t_hit *hit, double *closest);
int				hit_closest_plane(t_ray ray, t_plane *planes,
					t_hit *hit, double *closest);
int				hit_closest_cylinder(t_ray ray, t_cylinder *cylinders,
					t_hit *hit, double *closest);
int				hit_cylinder_side(t_ray ray, t_cylinder *cy, double *t);
int				solve_quadratic(t_coordinates d, t_coordinates oc,
					double r, double *t);
t_coordinates	compute_side_normal(t_ray r, t_cylinder *cy, double t);
void			set_cap_hit(t_cap_hit *cap, int top, double t);
int				find_closest_hit(double t_side, t_cap_hit cap0,
					t_cap_hit cap1, double *closest_t);
void			update_hit(t_hit *hit, t_ray ray, t_cylinder *cy,
					t_cyl_hits hits);

int				estimate_ts(t_cone_hit *hit, double *t_out);

#endif