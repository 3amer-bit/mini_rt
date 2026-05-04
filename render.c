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

static double	light_intensity(t_hit hit, t_scene scene)
{
	t_vec3	light_dir;

	light_dir = normalize(scale(scene.light.direction, -1));
	return (fmax(dot(hit.normal, light_dir), 0.0) * scene.light.brightness);
}

t_ray	get_ray(t_camera cam, t_coord viewport)
{
	t_ray	ray;

	ray.origin = cam.origin;
	ray.direction = add(
			cam.forward,
			add(
				scale(cam.right, viewport.x),
				scale(cam.up, viewport.y)
				)
			);
	return (ray);
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
		hit = intersect_sphere(&ray, &scene.objects[i]);
		if (hit.t > 0 && (closest_hit.t < 0 || hit.t < closest_hit.t))
			closest_hit = hit;
		i++;
	}
	return (closest_hit);
}

t_color	ray_gen(t_ray ray, t_scene scene)
{
	double	brightness;
	t_hit	hit;

	hit = trace_ray(ray, scene);
	if (hit.t < 0)
		return (background(ray));
	brightness = light_intensity(hit, scene);
	return ((t_color){
		hit.mat->albedo.x * brightness,
		hit.mat->albedo.y * brightness,
		hit.mat->albedo.z * brightness,
	});
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
