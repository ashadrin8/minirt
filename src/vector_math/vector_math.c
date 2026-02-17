/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 21:05:49 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/17 11:40:49 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_math.h"

t_vec3	vec_create(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	return (vec_create(a.x + b.x, a.y + b.y, a.z + b.z));
}

//ray-to-object calculations, distance checks
t_vec3	vec_subtract(t_vec3 a, t_vec3 b)
{
	return (vec_create(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3	vec_scale(t_vec3 vec, double s)
{
	t_vec3	result;

	result.x = vec.x * s;
	result.y = vec.y * s;
	result.z = vec.z * s;
	return (result);
}

//length = sqrt(x² + y² + z²)
double	vec_length(t_vec3 vec)
{
	double	length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (length);
}
