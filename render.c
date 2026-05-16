#include <math.h>
#include <stddef.h>
#include "vector.h"
#include "scene.h"
#include "minirt.h"

static t_color	background(t_ray ray)
{
	double	a;

	a = 0.5 * (ray.direction.y + 1.0);
	return ((t_color){
		(1.0 - a) * 1.0 + a * 0.5,
		(1.0 - a) * 1.0 + a * 0.7,
		(1.0 - a) * 1.0 + a * 1.0,
	});
}

static t_hit	trace_ray(t_ray ray, t_scene scene)
{
	t_hit	closest_hit;
	t_hit	hit;
	int		i;

	closest_hit = (t_hit){0};
	closest_hit.t = -1.0;
	i = 0;
	while (i < scene.obj_count)
	{
		hit = scene.objects[i].intersect(&ray, scene.objects[i].data);
		if (hit.t <= EPSILON)
		{
			i++;
			continue ;
		}
		if (closest_hit.t < EPSILON || hit.t < closest_hit.t)
			closest_hit = hit;
		i++;
	}
	return (closest_hit);
}

t_color	ray_gen(t_ray ray, t_scene scene)
{
	t_color	brightness;
	t_hit	hit;

	hit = trace_ray(ray, scene);
	if (hit.t < 0)
		return (background(ray));
	brightness = shade(hit, scene);
	return ((t_color){
		hit.mat->albedo.x * brightness.x,
		hit.mat->albedo.y * brightness.y,
		hit.mat->albedo.z * brightness.z,
	});
}

t_ray	get_ray(t_camera cam, t_coord viewport)
{
	t_ray	ray;

	ray.origin = cam.origin;
	ray.direction = normalize(
			add(
				cam.forward,
				add(
					scale(cam.right, viewport.x),
					scale(cam.up, viewport.y)
					)
				)
			);
	return (ray);
}

void	render(t_framebuf *fb, t_scene scene)
{
	t_pixel	pixel;
	t_coord	vp;
	double	aspect;
	double	scale;

	pixel.y = 0;
	aspect = (double) fb->width / fb->height;
	scale = tan(degrees_to_radians(scene.camera.fov) * 0.5);
	while (pixel.y < fb->height)
	{
		pixel.x = 0;
		while (pixel.x < fb->width)
		{
			vp.y = (1 - 2 * ((double) pixel.y / fb->height)) * scale;
			vp.x = (2 * ((double) pixel.x / fb->width) - 1) * aspect * scale;
			pixel.color = ray_gen(get_ray(scene.camera, vp), scene);
			ft_mlx_put_pixel(fb, &pixel);
			pixel.x++;
		}
		pixel.y++;
	}
}
