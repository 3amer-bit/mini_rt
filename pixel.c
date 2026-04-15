#include "minirt.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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
	*(unsigned int *)pixel_to_color = pixel->color;
}
