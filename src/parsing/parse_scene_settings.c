/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene_settings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:45:35 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/16 20:34:15 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_internal.h"

int	parse_general(char *line, t_scene *scene, t_parsing *p)
{
	if (check_singularity(line, scene) == ERROR)
		return (ERROR);
	p->i = 2;
	p->position = 1;
	while (line[p->i])
	{
		while (line[p->i] == ' ')
			p->i++;
		p->start = p->i;
		while (line[p->i] != ' ' && line[p->i])
			p->i++;
		p->len = p->i - p->start;
		p->parameter = ft_substr(line, p->start, p->len);
		if (!p->parameter)
			return (ERROR);
		if (p->validate_store(p, scene) == ERROR)
			return (free(p->parameter), ERROR);
		free(p->parameter);
		p->position++;
	}
	if (p->position != p->tot_pars + 1)
		return (ERROR);
	return (SUCCESS);
}

int	check_singularity(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "A ", 2) == 0)
	{
		if (scene->ambient.exists == 0)
			scene->ambient.exists = 1;
		else
			return (ERROR);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (scene->camera.exists == 0)
			scene->camera.exists = 1;
		else
			return (ERROR);
	}
	else if (ft_strncmp(line, "L ", 2) == 0)
	{
		if (scene->light.exists == 0)
			scene->light.exists = 1;
		else
			return (ERROR);
	}
	return (SUCCESS);
}

int	validate_store_ambient(t_parsing *p, t_scene *scene)
{
	double	number;

	if (p->position == 3)
		return (ERROR);
	if (p->position == 1)
	{
		if (ascii_to_double(p->parameter, &number) == ERROR)
			return (ERROR);
		if (number < 0.0 || number > 1.0)
			return (ERROR);
		scene->ambient.ratio = number;
	}
	if (p->position == 2)
	{
		if (validate_and_store_color(p->parameter,
				&scene->ambient.colors) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	validate_store_camera(t_parsing *p, t_scene *scene)
{
	int		fov;

	if (p->position == 4)
		return (ERROR);
	if (p->position == 1)
	{
		if (validate_and_store_coordinates(p->parameter,
				&scene->camera.coords) == ERROR)
			return (ERROR);
	}
	if (p->position == 2)
	{
		if (validate_and_store_vector(p->parameter,
				&scene->camera.forward) == ERROR)
			return (ERROR);
	}
	if (p->position == 3)
	{
		if (atoi_with_overflows(p->parameter, &fov) == ERROR)
			return (ERROR);
		scene->camera.view = fov;
	}
	return (SUCCESS);
}

int	validate_store_light(t_parsing *p, t_scene *s)
{
	double	brightness;

	if (p->position == 4)
		return (ERROR);
	if (p->position == 1)
	{
		if (validate_and_store_coordinates(p->parameter,
				&s->light.coords) == ERROR)
			return (ERROR);
	}
	if (p->position == 2)
	{
		if (ascii_to_double(p->parameter, &brightness) == ERROR)
			return (ERROR);
		if (brightness < 0.0 || brightness > 1.0)
			return (ERROR);
		s->light.brightness = brightness;
	}
	if (p->position == 3)
		return (validate_and_store_color(p->parameter, &s->light.color));
	return (SUCCESS);
}
