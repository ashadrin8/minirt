/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:31:43 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/22 18:37:28 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "defines.h"

void	free_cylinders_cones(t_scene *scene)
{
	t_cylinder	*cylinder;
	t_cone		*cone;

	while (scene->cylinders)
	{
		cylinder = scene->cylinders->next;
		free(scene->cylinders);
		scene->cylinders = cylinder;
	}
	while (scene->cones)
	{
		cone = scene->cones->next;
		free(scene->cones);
		scene->cones = cone;
	}
}

void	free_scene(t_scene *scene)
{
	t_plane		*plane;
	t_sphere	*sphere;

	while (scene->planes)
	{
		plane = scene->planes->next;
		free(scene->planes);
		scene->planes = plane;
	}
	while (scene->spheres)
	{
		sphere = scene->spheres->next;
		free(scene->spheres);
		scene->spheres = sphere;
	}
	free_cylinders_cones(scene);
}
