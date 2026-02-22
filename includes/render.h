/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:56:36 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/22 19:35:25 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define INF 1e30
# define EPS 1e-4
# include "defines.h"

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

t_coordinates	ray_at(t_ray ray, double t);

#endif