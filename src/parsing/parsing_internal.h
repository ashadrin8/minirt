/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:49:06 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/15 23:52:23 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_INTERNAL_H
# define PARSING_INTERNAL_H

# include "defines.h"

struct	s_parsing;
typedef int	(*t_validate_store_fn)(struct s_parsing *, t_scene *);

typedef struct	s_parsing
{
	int 	i;
	int		start;
	int		position;
	int		len;
	double	number;
	int		tot_pars;
	char	*parameter;
	t_validate_store_fn validate_store;
	// t - type, fn - function
	void	*current_object;
}	t_parsing;


//validate and store objects
int		validate_store_ambient(t_parsing *p, t_scene *scene);
int		validate_store_camera(t_parsing *p, t_scene *scene);
int		validate_store_light(t_parsing *p, t_scene *scene);
int		validate_store_sphere(t_parsing *p, t_scene *scene);
int		validate_store_plane(t_parsing *p, t_scene *scene);
int		validate_store_cylinder(t_parsing *p, t_scene *scene);
int		validate_store_cone(t_parsing *p, t_scene *scene);

//init
void	scene_init(t_scene	*scene);
int		plane_create(t_scene *scene);
int		sphere_create(t_scene *scene);
int		cylinder_create(t_scene *scene);
int		cone_create(t_scene *scene);

//utils
int		is_valid_rt(char *filename);
int		atoi_with_overflows(const char *str, int *value);
int		ascii_to_double(char *str, double *value);
int		potential_double_check(char *str);
int		potential_int_check(const char *str);

//color
int		validate_and_store_color(char *string, t_color *color);
int		color_assign(char *number, t_color *color, int position);

//coordinates
int		validate_and_store_coordinates(char *string, t_coordinates *coords);
int		coord_assign(char *number, t_coordinates *coords, int position);
int		validate_and_store_vector(char *string, t_coordinates *vector);
int		vector_assign(char *number, t_coordinates *vector, int position);


int		validate_and_parse(int argc, char **argv, t_scene *scene);
int		parse_line(char *line, t_scene *scene);
int		manage_geometric(char *line, t_scene *scene, t_parsing *p);
int		parse_general(char *line, t_scene *scene, t_parsing *p);
int		check_singularity(char *line, t_scene *scene);

#endif