/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashadrin <ashadrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 23:29:03 by chiarakappe       #+#    #+#             */
/*   Updated: 2026/02/12 14:59:56 by ashadrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_internal.h"


// Exit the program as failure
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// prints the window width & height
static void ft_hook()
// void* param
{
	// const mlx_t* mlx = param;
return ;
	// printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

void	context_init(mlx_t *mlx, mlx_image_t *img, t_scene *scene, t_mlx_context *con)
{
	con->img = img;
	con->mlx = mlx;
	con->scene = scene;
	con->width = WIDTH;
	con->height = HEIGHT;
}

void	resizing(int32_t width, int32_t height, void *con)
{
	t_mlx_context	*ctx;

	ctx = (t_mlx_context *)con;
	mlx_delete_image(ctx->mlx, ctx->img);
	ctx->img = mlx_new_image(ctx->mlx, width, height);
	if (!ctx->img || (mlx_image_to_window(ctx->mlx, ctx->img, 0, 0) < 0))
		ft_error();
	ctx->width = width;
	ctx->height = height;
	render_scene(ctx->scene, ctx->img);
}

int32_t	create_window(t_scene *scene)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_mlx_context	con;

	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
	ft_error();
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	ft_error();
	context_init(mlx, img, scene, &con);

	mlx_resize_hook(mlx, resizing, &con);
	render_scene(scene, img);

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}


//The management of your window must remain fluid: switching to another window,
//minimization, etc.

// • The program displays the image in a window and respects the following rules:
// ◦ Pressing ESC must close the window and quit the program cleanly.
// ◦ Clicking on the red cross on the window frame must close the window and quit
// the program cleanly.
// ◦ The use of images from the minilibX library is strongly recommended.