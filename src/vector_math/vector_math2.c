/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 11:39:21 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/17 11:42:51 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec3	vec_normalize(t_vec3 vec)
{
	double	len;

	len = vec_length(vec);
	if (len == 0)
		return (vec_create(0, 0, 0));
	return (vec_scale(vec, 1 / len));
}

// dot product of two vectors is a number that tells how much 
//they point in the same direction
// used to compute pixel's light intensty
// positive - vectors point generally in the same direction
// negative - vectors point generally in opposite directions
// 0 - vectors are perpendicular
// for normalized vectors it's either -1, 0 or 1
double	vec_dot(t_vec3 a, t_vec3 b)
{
	double	result;

	result = (a.x * b.x + a.y * b.y + a.z * b.z);
	return (result);
}

//gives a vector perpendicular to both input vectors, with direction 
// determined by the right-hand rule
t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

//rotates a vector around a given axis by a specified angle 
//(in radians)
//used for changing the camera view
t_vec3	vec_rotate(t_vec3 v, t_vec3 axis, double angle)
{
	double	cos_theta;
	double	sin_theta;
	t_vec3	term1;
	t_vec3	term2;
	t_vec3	term3;

	cos_theta = cos(angle);
	sin_theta = sin(angle);
	term1 = vec_scale(v, cos_theta);
	term2 = vec_scale(vec_cross(axis, v), sin_theta);
	term3 = vec_scale(axis, vec_dot(axis, v) * (1 - cos_theta));
	return (vec_add(vec_add(term1, term2), term3));
}
