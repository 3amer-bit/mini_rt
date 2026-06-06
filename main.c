#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdlib.h>
#include "./minilibx-linux/mlx.h"
#include "minirt.h"
#include "libft/inc/libft.h"

static int	setup_img(t_window *win_ctx)
{
	t_framebuf	*framebuf;

	framebuf = win_ctx->framebuf;
	framebuf->img_ptr = mlx_new_image(
			win_ctx->mlx_ptr, win_ctx->width, win_ctx->height);
	if (!framebuf->img_ptr)
		return (0);
	framebuf->addr = mlx_get_data_addr(
			framebuf->img_ptr, &framebuf->bits_per_pixel,
			&framebuf->line_length, &framebuf->endian
			);
	framebuf->width = win_ctx->width;
	framebuf->height = win_ctx->height;
	return (1);
}

static int	setup_hooks(t_window *window)
{
	mlx_hook(window->win_ptr, KeyPress, KeyPressMask, handle_keypress, window);
	mlx_hook(
		window->win_ptr,
		DestroyNotify,
		StructureNotifyMask,
		handle_destroy_structure_notify,
		window
		);
	// mlx_mouse_hook(win_ctx->win_ptr, handle_mouse, window);
	mlx_loop_hook(window->mlx_ptr, loop_hook, window);
	return (1);
}

static int	init_window(t_window *win, char **argv)
{
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		return (0);
	mlx_get_screen_size(win->mlx_ptr, &win->width, &win->height);
	win->width = 1280;
	win->height = 720;
	win->win_ptr = mlx_new_window(
			win->mlx_ptr, win->width, win->height, "Mini RT");
	if (!win->win_ptr)
	{
		mlx_destroy(win);
		return (0);
	}
	if (!setup_img(win))
	{
		mlx_destroy(win);
		return (0);
	}
	win->redraw = 0;
	win->scene = parse_scene(argv[1]);
	
	return (1);
}

static void	check_args(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		ft_error("Usage: ./minirt <scene.rt>");
	len = ft_strlen(argv[1]);
	if (len < 3 || ft_strncmp(argv[1] + len - 3, ".rt", 3) != 0)
		ft_error("File must have .rt extension");
}

int	main(int argc, char **argv)
{
	t_window	win_ctx;
	t_framebuf	framebuf;

	check_args(argc, argv);
	win_ctx.framebuf = &framebuf;
	if (!init_window(&win_ctx, argv))
		return (EXIT_FAILURE);
	setup_hooks(&win_ctx);
	render(&framebuf, win_ctx.scene);
	mlx_put_image_to_window(
		win_ctx.mlx_ptr, win_ctx.win_ptr, win_ctx.framebuf->img_ptr, 0, 0);
	mlx_loop(win_ctx.mlx_ptr);
	free_scene(&win_ctx.scene);
	return (EXIT_SUCCESS);
}
