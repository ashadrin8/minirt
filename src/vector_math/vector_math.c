/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 21:05:49 by ashadrin          #+#    #+#             */
/*   Updated: 2026/01/29 19:45:06 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec3	vec_create(double x, double y, double z)
{
	t_vec3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

//moving along the ray
// t_vec3	vec_add(t_vec3 a, t_vec3 b)
// {
// 	return (vec_create(a.x + b.x, a.y + b.y, a.z + b.z));
// }

//ray-to-object calculations, distance checks
t_vec3	vec_subtract(t_vec3 a, t_vec3 b)
{
	return (vec_create(a.x - b.x, a.y - b.y, a.z - b.z));
}

//scalar multiplication 
//(multiplying each component of a vector by a scalar value)
// scalar - not a vector, but a single number
//moving in a direction for a certain number of steps
// t_vec3	vec_scale(t_vec3 vec, double s)
// {
// 	t_vec3	result;

// 	result.x = vec.x * s;
// 	result.y = vec.y * s;
// 	result.z = vec.z * s;
// 	return (result);
// }

//length = sqrt(x² + y² + z²)
double	vec_length(t_vec3 vec)
{
	double length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (length);
}

// normalization in this case - taking a direction
//and making it have length 1 without changing which way it points
//(so that there's no distance implied and we can operate vectors)
// applied to ALL vector directions
// t_vec3	vec_normalize(t_vec3 vec)
// {
// 	double len;

// 	len = vec_length(vec);
// 	if (len == 0)
// 		return (vec_create(0, 0, 0));
// 	//because we can't divide by 0
// 	return (vec_scale(vec, 1 / len));
// 	// 1 / len - factor that shrinks the vector to length 1
// }

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
