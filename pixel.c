#include "minirt.h"

static double	clamp(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static int	create_trgb(t_color c)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	tr;

	red = 255.999 * clamp(c.r, 0.0, 1);
	green = 255.999 * clamp(c.g, 0.0, 1);
	blue = 255.999 * clamp(c.b, 0.0, 1);
	tr = 255.999 * clamp(c.t, 0.0, 1);
	return (tr << 24 | red << 16 | green << 8 | blue);
}

void	ft_mlx_put_pixel(t_framebuf *framebuf, t_pixel *pixel)
{
	int		bytes_per_pixel;
	char	*pixel_to_color;

	if (pixel->x < 0 || pixel->x > framebuf->width)
		return ;
	if (pixel->y < 0 || pixel->y > framebuf->height)
		return ;
	bytes_per_pixel = framebuf->bits_per_pixel / 8;
	pixel_to_color = framebuf->addr
		+ (pixel->x * bytes_per_pixel + pixel->y * framebuf->line_length);
	*(unsigned int *)pixel_to_color = create_trgb(pixel->color);
}
