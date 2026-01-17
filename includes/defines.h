/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:35:19 by ashadrin          #+#    #+#             */
/*   Updated: 2026/01/17 10:29:35 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
# include "get_next_line.h"

# include <MLX42/MLX42.h>

# define ERROR -1
# define SUCCESS 0

# define WIDTH 800
# define HEIGHT 600  

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
	t_coordinates	vector;
	int				view;
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
}	t_scene;


void		scene_init(t_scene	*scene);
int			validate_and_parse(int argc, char **argv, t_scene *scene);
int32_t		create_window(t_scene *scene);

#endif