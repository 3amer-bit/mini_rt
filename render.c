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
		hit = intersect_sphere(&ray, &scene.objects[i]);
		if (
			hit.t > EPSILON
			&& (closest_hit.t < EPSILON || hit.t < closest_hit.t)
		)
			closest_hit = hit;
		i++;
	}
	return (closest_hit);
}

int	intersects_anything(t_ray ray, t_scene scene, double max_dist)
{
	int		i;
	t_hit	hit;

	i = 0;
	while (i < scene.obj_count)
	{
		hit = intersect_sphere(&ray, &scene.objects[i]);
		if (hit.t > EPSILON && hit.t < max_dist)
			return (1);
		i++;
	}
	return (0);
}

int	in_shadow(t_hit hit, t_scene scene, t_vec3 light_dir)
{
	t_ray	shadow_ray;
	double	dist_to_light;

	shadow_ray.origin = hit.point;
	shadow_ray.direction = sub(scene.light.origin, hit.point);
	dist_to_light = vec_len(light_dir);
	return (intersects_anything(shadow_ray, scene, dist_to_light));
}

t_color	ambient_color(t_scene scene)
{
	return (scale(scene.ambient_light.color, scene.ambient_light.brightness));
}

t_color	diffuse_color(t_hit hit, t_scene scene, t_vec3 light_dir)
{
	return (scale(
			scene.light.color,
			fmax(dot(hit.normal, light_dir), 0.0) * scene.light.brightness)
	);
}

t_vec3	reflect(t_vec3 normal, t_vec3 light_dir)
{
	return (sub(light_dir, scale(normal, 2 * dot(light_dir, normal))));
}

t_color	specular_color(t_hit hit, t_scene scene, t_vec3 light_dir)
{
	t_vec3	reflect_dir;
	t_vec3	view_dir;
	double	specular;

	reflect_dir = reflect(hit.normal, scale(light_dir, -1.0));
	view_dir = normalize(sub(scene.camera.origin, hit.point));
	specular = pow(fmax(dot(view_dir, reflect_dir), 0.0), 32);
	return (scale(scene.light.color, specular * scene.light.brightness));
}

static t_color	light_intensity(t_hit hit, t_scene scene)
{
	t_vec3	light_dir;
	t_color	color;

	color = ambient_color(scene);
	light_dir = normalize(sub(scene.light.origin, hit.point));
	if (!in_shadow(hit, scene, light_dir))
	{
		color = add(
				color,
				add(
					scale(diffuse_color(hit, scene, light_dir), 0.7),
					scale(specular_color(hit, scene, light_dir), 0.3)
					)
				);
	}
	return (color);
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

t_color	ray_gen(t_ray ray, t_scene scene)
{
	t_color	brightness;
	t_hit	hit;

	hit = trace_ray(ray, scene);
	if (hit.t < 0)
		return (background(ray));
	brightness = light_intensity(hit, scene);
	return ((t_color){
		hit.mat->albedo.x * brightness.x,
		hit.mat->albedo.y * brightness.y,
		hit.mat->albedo.z * brightness.z,
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
