#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>
#include "./minilibx-linux/mlx.h"
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

int	handle_keypress(int keysym, t_window *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy(data);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

int	handle_destroy_structure_notify(t_window *data)
{
	mlx_destroy(data);
	exit(EXIT_SUCCESS);
}
