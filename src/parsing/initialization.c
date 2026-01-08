/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:54:15 by ashadrin          #+#    #+#             */
/*   Updated: 2026/01/07 22:41:11 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_internal.h"

void	scene_init(t_scene	*scene)
{
	scene->ambient.exists = 0;
	scene->camera.exists = 0;
	scene->light.exists = 0;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
}

int	plane_create(t_scene *scene)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (ERROR);
	if (scene->planes == NULL)
		scene->planes = plane;
	else
		scene->last_plane->next = plane;
	scene->last_plane = plane;
	plane->next = NULL;
	return (SUCCESS);
}

int	sphere_create(t_scene *scene)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (ERROR);
	if (scene->spheres == NULL)
		scene->spheres = sphere;
	else
		scene->last_sphere->next = sphere;
	scene->last_sphere = sphere;
	sphere->next = NULL;
	return (SUCCESS);
}

int	cylinder_create(t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (ERROR);
	if (scene->cylinders == NULL)
		scene->cylinders = cylinder;
	else
		scene->last_cylinder->next = cylinder;
	scene->last_cylinder = cylinder;
	cylinder->next = NULL;
	return (SUCCESS);
}
