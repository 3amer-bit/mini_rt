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

static t_color	background(t_ray ray)
{
	t_vec3	unit_direction;
	double	a;

	unit_direction = normalize(ray.direction);
	a = 0.5 * (unit_direction.y + 1.0);
	return ((t_color){
		1,
		(1.0 - a) * 1.0 + a * 0.5,
		(1.0 - a) * 1.0 + a * 0.7,
		(1.0 - a) * 1.0 + a * 1.0,
	});
}

double	light_intensity(t_vec3 intersection, t_sphere sphere)
{
	t_point3	light;
	t_vec3		normal;
	t_vec3		light_dir;

	light = (t_point3){-1, -1, -1};
	normal = normalize(sub(intersection, sphere.origin));
	light_dir = normalize(scale(-1, light));
	return (fmax(dot(normal, light_dir), 0.0));
}

static t_color	trace_ray(t_coord *coord)
{
	t_ray		ray;
	t_sphere	sphere;
	double		t;
	t_vec3		intersection;
	double		intensity;

	ray.origin = (t_point3){0, 0, 1.1};
	ray.direction = (t_vec3){(coord->x), (coord->y), -1};
	sphere.origin = (t_point3){0, 0, 0};
	sphere.radius = 0.5;
	sphere.color = (t_color){1, 1, 0, 0};
	t = intersect(&ray, &sphere);
	if (t < 0)
		return (background(ray));
	intersection = add(ray.origin, scale(t, ray.direction));
	intensity = light_intensity(intersection, sphere);
	return ((t_color){
		1,
		sphere.color.r * intensity,
		sphere.color.g * intensity,
		sphere.color.b * intensity,
	});
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
