/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:31:09 by ashadrin          #+#    #+#             */
/*   Updated: 2026/02/16 22:50:02 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "defines.h"

static void print_color(const t_color *c, const char *label) {
	printf("%s: (R: %d, G: %d, B: %d)\n", label, c->red, c->green, c->blue);
}

static void print_coordinates(const t_coordinates *coord, const char *label) {
	printf("%s: (x: %.2f, y: %.2f, z: %.2f)\n", label, coord->x, coord->y, coord->z);
}

void print_scene(const t_scene *scene) {
	printf("--- Scene Debug Info ---\n");
	// Ambient Light
	printf("Ambient Light: exists=%d, ratio=%.2f\n", scene->ambient.exists, scene->ambient.ratio);
	print_color(&scene->ambient.colors, "Ambient Color");

	// Camera
	printf("Camera: exists=%d\n", scene->camera.exists);
	print_coordinates(&scene->camera.coords, "Camera Coords");
	print_coordinates(&scene->camera.forward, "Camera Vector");
	printf("Camera FOV: %d\n", scene->camera.view);

	// Light
	printf("Light: exists=%d, brightness=%.2f\n", scene->light.exists, scene->light.brightness);
	print_coordinates(&scene->light.coords, "Light Coords");
	print_color(&scene->light.color, "Light Color");

	// Spheres
	t_sphere *sp = scene->spheres;
	int i = 0;
	while (sp) {
		printf("Sphere #%d:\n", i++);
		print_coordinates(&sp->center, "  Center");
		printf("  Diameter: %.2f\n", sp->diameter);
		print_color(&sp->color, "  Color");
		sp = sp->next;
	}

	// Planes
	t_plane *pl = scene->planes;
	i = 0;
	while (pl) {
		printf("Plane #%d:\n", i++);
		print_coordinates(&pl->point, "  Point");
		print_coordinates(&pl->vector, "  Vector");
		print_color(&pl->color, "  Color");
		pl = pl->next;
	}

	// Cylinders
	t_cylinder *cy = scene->cylinders;
	i = 0;
	while (cy) {
		printf("Cylinder #%d:\n", i++);
		print_coordinates(&cy->center, "  Center");
		print_coordinates(&cy->vector, "  Vector");
		printf("  Diameter: %.2f\n", cy->diameter);
		printf("  Height: %.2f\n", cy->height);
		print_color(&cy->color, "  Color");
		cy = cy->next;
	}
	// Cones
	t_cone *co = scene->cones;
	i = 0;
	while (co) {
		printf("Cone #%d:\n", i++);
		print_coordinates(&co->apex, "  Apex");
		print_coordinates(&co->axis, "  Axis");
		printf("  Diameter: %.2f\n", co->diameter);
		printf("  Height: %.2f\n", co->height);
		print_color(&co->color, "  Color");
		co = co->next;
	}
	printf("--- End Scene Debug Info ---\n");
}

#include "defines.h"

void	free_scene(t_scene *scene)
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;
	t_cone		*cone;
	
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

int main(int argc, char **argv)
{
	t_scene	scene;

	scene_init(&scene);
	validate_and_parse(argc, argv, &scene);
	print_scene(&scene);
	create_window(&scene);
	free_scene(&scene);

	return (0);
}
