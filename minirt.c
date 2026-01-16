/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiarakappe <chiarakappe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:31:09 by ashadrin          #+#    #+#             */
/*   Updated: 2026/01/16 23:47:03 by chiarakappe      ###   ########.fr       */
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
	print_coordinates(&scene->camera.vector, "Camera Vector");
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
	printf("--- End Scene Debug Info ---\n");
}

#include "defines.h"

int main(int argc, char **argv)
{
	t_scene	scene;

	scene_init(&scene);
	validate_and_parse(argc, argv, &scene);
	create_window(&scene);
	print_scene(&scene);

	return (0);
}
