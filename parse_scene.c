/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:58:01 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "vector.h"

void	parse_ambient(t_scene *scene, char **parts)
{
	if (scene->has_ambient)
		ft_error(scene, "Duplicate ambient light");
	check_argc(scene, parts, 3);
	scene->ambient_light.brightness = parse_ratio(scene, parts[1]);
	scene->ambient_light.color = parse_color(scene, parts[2]);
	scene->has_ambient = 1;
}

void	parse_camera(t_scene *scene, char **parts)
{
	t_vec3	world_up;

	if (scene->has_camera)
		ft_error(scene, "Duplicate camera");
	check_argc(scene, parts, 4);
	scene->camera.origin = parse_vec3(scene, parts[1]);
	scene->camera.forward = parse_direction(scene, parts[2]);
	check_number(scene, parts[3]);
	scene->camera.fov = ft_atof(parts[3]);
	check_range(scene, scene->camera.fov, 0.0, 180.0);
	world_up = (t_vec3){0, 1, 0};
	if (fabs(scene->camera.forward.y) > 1.0 - EPSILON)
		world_up = (t_vec3){1, 0, 0};
	scene->camera.right = normalize(cross(scene->camera.forward, world_up));
	scene->camera.up = cross(scene->camera.right, scene->camera.forward);
	scene->has_camera = 1;
}

void	parse_light(t_scene *scene, char **parts)
{
	int	i;

	check_argc(scene, parts, 4);
	if (scene->light_count >= 100)
		ft_error(scene, "Too many lights");
	i = scene->light_count;
	scene->lights[i].origin = parse_vec3(scene, parts[1]);
	scene->lights[i].brightness = parse_ratio(scene, parts[2]);
	scene->lights[i].color = parse_color(scene, parts[3]);
	scene->light_count++;
}
