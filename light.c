#include <math.h>
#include "vector.h"
#include "minirt.h"

static t_color	ambient_color(t_scene scene)
{
	return (scale(scene.ambient_light.color, scene.ambient_light.brightness));
}

static t_color	diffuse_color(t_hit hit, t_light light, t_vec3 light_dir)
{
	double	dot_product;

	dot_product = fmax(dot(hit.normal, light_dir), 0.0);
	return (scale(light.color, dot_product * light.brightness));
}

static t_color	specular_color(t_hit hit, t_light light, t_vec3 light_dir)
{
	t_vec3	reflect_dir;
	double	specular;

	reflect_dir = reflect(hit.normal, scale(light_dir, -1.0));
	specular = pow(
			fmax(dot(hit.view_dir, reflect_dir), 0.0),
			hit.mat->shininess
			);
	return (scale(light.color, specular * light.brightness));
}

static t_color	eval_light(t_hit hit, t_scene scene, t_light light)
{
	t_vec3	light_dir;
	t_color	contribution;

	if (in_shadow(hit, scene, light))
		return ((t_color){0, 0, 0});
	light_dir = normalize(sub(light.origin, hit.point));
	contribution = add(
			scale(diffuse_color(hit, light, light_dir), hit.mat->diffuse),
			scale(specular_color(hit, light, light_dir), hit.mat->specular)
			);
	return (contribution);
}

t_color	shade(t_hit hit, t_scene scene)
{
	t_color	color;
	int		i;

	color = ambient_color(scene);
	i = 0;
	while (i < scene.light_count)
	{
		color = add(
				color,
				eval_light(hit, scene, scene.lights[i])
				);
		i++;
	}
	return (color);
}
