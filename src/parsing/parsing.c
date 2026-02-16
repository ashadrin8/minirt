/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:52:28 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/16 21:59:30 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_internal.h"

int	validate_and_parse(int argc, char **argv, t_scene *scene)
{
	int		fd;
	char	*line;
	char	*trimmed;

	if (argc != 2)
		return (ERROR);
	if (!is_valid_rt(argv[1]))
		return (ERROR);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ERROR);
	line = get_next_line(fd);
	while (line != NULL)
	{
		trimmed = ft_strtrim(line, " \n\r\t");
		if (trimmed[0] != '\0')
			parse_line(trimmed, scene);
		free(trimmed);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (SUCCESS);
}

int	parse_line(char *line, t_scene *scene)
{
	t_parsing	p;

	if (ft_strncmp(line, "A ", 2) == 0)
	{
		p.validate_store = &validate_store_ambient;
		p.tot_pars = 2;
		return (parse_general(line, scene, &p));
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		p.validate_store = &validate_store_camera;
		p.tot_pars = 3;
		return (parse_general(line, scene, &p));
	}
	if (ft_strncmp(line, "L ", 2) == 0)
	{
		p.validate_store = &validate_store_light;
		p.tot_pars = 3;
		return (parse_general(line, scene, &p));
	}
	if (!ft_strncmp(line, "pl ", 3) || !ft_strncmp(line, "sp ", 3)
		|| !ft_strncmp(line, "cy ", 3) || !ft_strncmp(line, "co ", 3))
		return (manage_geometric(line, scene, &p));
	return (ERROR);
}

int	manage_further_geometric(char *line, t_scene *scene, t_parsing *p)
{
	if (ft_strncmp(line, "cy ", 3) == 0)
	{
		if (cylinder_create(scene) == ERROR)
			return (ERROR);
		p->validate_store = &validate_store_cylinder;
		p->tot_pars = 5;
		return (parse_general(line, scene, p));
	}
	if (ft_strncmp(line, "co ", 3) == 0)
	{
		if (cone_create(scene) == ERROR)
			return (ERROR);
		p->validate_store = &validate_store_cone;
		p->tot_pars = 5;
		return (parse_general(line, scene, p));
	}
	return (ERROR);
}

int	manage_geometric(char *line, t_scene *scene, t_parsing *p)
{	
	if (ft_strncmp(line, "pl ", 3) == 0)
	{
		if (plane_create(scene) == ERROR)
			return (ERROR);
		p->validate_store = &validate_store_plane;
		p->tot_pars = 3;
		return (parse_general(line, scene, p));
	}
	if (ft_strncmp(line, "sp ", 3) == 0)
	{
		if (sphere_create(scene) == ERROR)
			return (ERROR);
		p->validate_store = &validate_store_sphere;
		p->tot_pars = 3;
		return (parse_general(line, scene, p));
	}
	if ((ft_strncmp(line, "cy ", 3) == 0) || (ft_strncmp(line, "co ", 3) == 0))
		return (manage_further_geometric(line, scene, p));
	return (ERROR);
}
