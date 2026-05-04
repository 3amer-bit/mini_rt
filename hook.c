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
		mlx_destroy(data);
		exit(EXIT_SUCCESS);
	}
	if (keysym == XK_w)
	{
		data->redraw = 1;
		data->scene.camera.origin = add(data->scene.camera.origin, scale(data->scene.camera.forward, 0.5));
	}
	if (keysym == XK_s)
	{
		data->redraw = 1;
		data->scene.camera.origin = sub(data->scene.camera.origin, scale(data->scene.camera.forward, 0.5));
	}
	if (keysym == XK_d)
	{
		data->redraw = 1;
		data->scene.camera.origin = add(data->scene.camera.origin, scale(data->scene.camera.right, 0.5));
	}
	if (keysym == XK_a)
	{
		data->redraw = 1;
		data->scene.camera.origin = sub(data->scene.camera.origin, scale(data->scene.camera.right, 0.5));
	}
	if (keysym == XK_q)
	{
		data->redraw = 1;
		data->scene.camera.origin = add(data->scene.camera.origin, scale(data->scene.camera.up, 0.5));
	}
	if (keysym == XK_e)
	{
		data->redraw = 1;
		data->scene.camera.origin = sub(data->scene.camera.origin, scale(data->scene.camera.up, 0.5));
	}
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
	mlx_destroy(data);
	exit(EXIT_SUCCESS);
}
