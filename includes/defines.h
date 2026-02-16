/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:35:19 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/16 14:32:18 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

# include <MLX42/MLX42.h>

# define ERROR -1
# define SUCCESS 0

# define WIDTH 800
# define HEIGHT 800  

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

typedef struct	s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct	s_coordinates
{
	double	x;
	double	y;
	double	z;
}	t_coordinates;

typedef t_coordinates t_vec3;

typedef struct	s_am_light
{
	int		exists;
	double	ratio;
	t_color	colors;	
}	t_am_light;

typedef struct	s_camera
{
	int				exists;
	t_coordinates	coords;
	t_vec3			forward;
	t_vec3			right;
	t_vec3			up;
	int				view;

	t_vec3			horizontal;
	t_vec3			vertical;
	t_vec3			llc;
}	t_camera;

typedef struct	s_light
{
	int				exists;
	t_coordinates	coords;
	float			brightness;
	t_color			color;
}	t_light;

typedef struct s_sphere t_sphere;
struct	s_sphere
{
	t_coordinates	center;
	float			diameter;
	t_color			color;
	t_sphere		*next;
};

typedef struct	s_plane t_plane;
struct	s_plane
{
	t_coordinates	point;
	t_coordinates	vector;
	t_color			color;
	t_plane			*next;
};

typedef struct	s_cylinder t_cylinder;
struct	s_cylinder
{
	t_coordinates	center;
	t_coordinates	vector;
	double			diameter;
	double			height;
	t_color			color;
	t_cylinder		*next;
};

typedef struct  s_cone t_cone;
struct  s_cone
{
    t_coordinates   apex;
    t_vec3          axis;
    double          height;
    double          diameter;
    double          radius;
    double          slope;
	t_color			color;
    t_cone          *next;
}; 

typedef struct  c_cone_hit
{
    t_vec3  oc;
    double  m;
    double  n;
    double  A;
    double  B;
    double  C;
    double  discriminant;
    double  t0;
    double  t1;
	t_vec3	P;
}   t_cone_hit;

typedef struct s_scene
{
	t_am_light	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	*spheres;
	t_sphere	*last_sphere;
	t_plane		*planes;
	t_plane		*last_plane;
	t_cylinder	*cylinders;
	t_cylinder	*last_cylinder;
	t_cone		*cones;
	t_cone		*last_cone;
}	t_scene;


void		scene_init(t_scene	*scene);
int			validate_and_parse(int argc, char **argv, t_scene *scene);
int32_t		create_window(t_scene *scene);

#endif