/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 13:47:58 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/30 13:47:59 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include "./minilibx-linux/mlx.h"
#include "vector.h"
#include "minirt.h"

void	mlx_destroy(t_window *win_ctx)
{
	if (win_ctx->framebuf && win_ctx->framebuf->img_ptr)
		mlx_destroy_image(win_ctx->mlx_ptr, win_ctx->framebuf->img_ptr);
	if (win_ctx->win_ptr)
		mlx_destroy_window(win_ctx->mlx_ptr, win_ctx->win_ptr);
	mlx_destroy_display(win_ctx->mlx_ptr);
	free(win_ctx->mlx_ptr);
}

static void	clear_image(t_framebuf *img, int color)
{
	int	i;
	int	total;
	int	*pixels;

	i = 0;
	pixels = (int *)img->addr;
	total = img->width * img->height;
	while (i < total)
		pixels[i++] = color;
}

int	handle_keypress(int keysym, t_window *data)
{
	if (keysym == XK_Escape)
	{
		free_scene(&data->scene);
		mlx_destroy(data);
		exit(EXIT_SUCCESS);
	}
	data->redraw = move_camera(keysym, &data->scene.camera);
	return (1);
}

int	loop_hook(t_window *data)
{
	if (data->redraw)
	{
		clear_image(data->framebuf, 0);
		render(data->framebuf, data->scene);
		mlx_put_image_to_window(
			data->mlx_ptr,
			data->win_ptr,
			data->framebuf->img_ptr,
			0,
			0);
		data->redraw = 0;
	}
	return (1);
}

int	handle_destroy_structure_notify(t_window *data)
{
	free_scene(&data->scene);
	mlx_destroy(data);
	exit(EXIT_SUCCESS);
}
