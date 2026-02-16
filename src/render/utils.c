/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:35:24 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/16 14:21:39 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

uint32_t	rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int clamp(int value)
{
	if (value < 0)
		return 0;
	if (value > 255)
		return 255;
	return value;
}

t_coordinates	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(ray.direction, t)));
}
