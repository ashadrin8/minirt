/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:35:24 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/01/26 18:59:13 by chiarakappe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

uint32_t	rgba(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

/* normalize a vector means:
Scale it so its length (magnitude) is exactly 1. */

void normalize(t_coordinates *v)
{
	double len;

	len = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (len == 0)
		return;
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

// dot() measures vector alignment and length
double dot(t_coordinates a, t_coordinates b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

int clamp(int value)
{
	if (value < 0)
		return 0;
	if (value > 255)
		return 255;
	return value;
}
