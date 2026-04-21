#include <math.h>
#include "vector.h"
#include "minirt.h"

static double	intersect(t_ray *ray, t_sphere *sphere)
{
	double		discriminant;
	double		a;
	double		b;
	double		c;
	t_vec3		oc;

	oc = sub(ray->origin, sphere->origin);
	a = dot(ray->direction, ray->direction);
	b = 2 * dot(oc, ray->direction);
	c = dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return ((-b - sqrt(discriminant)) / (2 * a));
}

static unsigned int	trace_ray(t_coord *coord)
{
	t_ray		ray;
	t_sphere	sphere;
	double		intersection;

	ray.origin = (t_point3){0, 0, -2};
	ray.direction = (t_vec3){(coord->x), (coord->y), 1};
	sphere.origin = (t_point3){0, 0, 0};
	sphere.radius = 0.5;
	intersection = intersect(&ray, &sphere);
	if (intersection < 0)
		return (create_trgb(255, 0, 0, 0));
	return (create_trgb(255, 0, 50, 150));
}

void	render(t_framebuf *framebuf)
{
	int		i;
	int		j;
	t_pixel	pixel;
	t_coord	coord;
	double	aspect_ratio;

	j = 0;
	aspect_ratio = (double) framebuf->width / framebuf->height;
	while (j < framebuf->height)
	{
		i = 0;
		while (i < framebuf->width)
		{
			pixel.x = i;
			pixel.y = j;
			coord.x = (((double) i / framebuf->width) * 2 - 1) * aspect_ratio;
			coord.y = 1 - ((double) j / framebuf->height) * 2;
			pixel.color = trace_ray(&coord);
			ft_mlx_put_pixel(framebuf, &pixel);
			i++;
		}
		j++;
	}
}
