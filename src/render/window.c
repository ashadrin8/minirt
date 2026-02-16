/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:29:03 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/12 18:39:28 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"

static void	ft_error_exit(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	resizing(int32_t width, int32_t height, void *con)
{
	t_mlx_context	*ctx;

	ctx = (t_mlx_context *)con;
	mlx_delete_image(ctx->mlx, ctx->img);
	ctx->img = mlx_new_image(ctx->mlx, width, height);
	if (!ctx->img || (mlx_image_to_window(ctx->mlx, ctx->img, 0, 0) < 0))
		ft_error_exit();
	ctx->width = width;
	ctx->height = height;
	render_scene(ctx->scene, ctx->img);
}

void	keys(mlx_key_data_t keydata, void *con)
{
	t_mlx_context	*ctx;

	ctx = (t_mlx_context *)con;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(ctx->mlx);
	else if (keydata.action == MLX_PRESS)
	{
		handle_camera_rotation(keydata, ctx->scene);
		camera_prepare_orientation(&ctx->scene->camera, ctx->img);
		render_scene(ctx->scene, ctx->img);
	}
}

void	closing(void *con)
{
	t_mlx_context	*ctx;

	ctx = (t_mlx_context *)con;
	mlx_close_window(ctx->mlx);
}

int32_t	create_window(t_scene *scene)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_mlx_context	con;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		ft_error_exit();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error_exit();
	con.img = img;
	con.mlx = mlx;
	con.scene = scene;
	con.width = WIDTH;
	con.height = HEIGHT;
	render_scene(scene, img);
	mlx_resize_hook(mlx, resizing, &con);
	mlx_key_hook(mlx, keys, &con);
	mlx_close_hook(mlx, closing, &con);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
