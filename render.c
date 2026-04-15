#include "minirt.h"

unsigned int	gradient(t_coord *coord)
{
	return (create_trgb(
			0,
			(int) 255.999 * coord->x,
			(int) 255.999 * coord->y,
			0
		));
}

void	render(t_framebuf *framebuf)
{
	int		i;
	int		j;
	t_pixel	pixel;
	t_coord	coord;

	j = 0;
	while (j < framebuf->height)
	{
		i = 0;
		while (i < framebuf->width)
		{
			pixel.x = i;
			pixel.y = j;
			coord.x = ((double) i / framebuf->width);
			coord.y = 1 - ((double) j / framebuf->height);
			pixel.color = gradient(&coord);
			ft_mlx_put_pixel(framebuf, &pixel);
			i++;
		}
		j++;
	}
}
