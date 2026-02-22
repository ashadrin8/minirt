/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:35:08 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/22 19:35:11 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_MATH_H
# define VECTOR_MATH_H

# include "defines.h"
# include "math.h"

t_vec3	vec_create(double x, double y, double z);
t_vec3	vec_add(t_vec3 a, t_vec3 b);
t_vec3	vec_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec_scale(t_vec3 vec, double s);
double	vec_length(t_vec3 vec);
t_vec3	vec_normalize(t_vec3 vec);
double	vec_dot(t_vec3 a, t_vec3 b);
t_vec3	vec_cross(t_vec3 a, t_vec3 b);
t_vec3	vec_rotate(t_vec3 v, t_vec3 axis, double angle);

#endif