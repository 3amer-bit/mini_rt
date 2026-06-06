/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 00:37:57 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/06 12:39:19 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"
#include "minirt.h"
#include "vector.h"

void	parse_ambient(t_scene *scene, char **parts)
{
	if (scene->has_ambient)
		ft_error("Duplicate ambient light");
	scene->ambient_light.brightness = ft_atof(parts[1]);
	scene->ambient_light.color = parse_color(parts[2]);
	scene->has_ambient = 1;
}

void	parse_camera(t_scene *scene, char **parts)
{
	t_vec3	world_up;

	if (scene->has_camera)
		ft_error("Duplicate camera");
	scene->camera.origin = parse_vec3(parts[1]);
	scene->camera.forward = normalize(parse_vec3(parts[2]));
	scene->camera.fov = ft_atof(parts[3]);
	world_up = (t_vec3){0, 1, 0};
	scene->camera.right = normalize(cross(scene->camera.forward, world_up));
	scene->camera.up = cross(scene->camera.right, scene->camera.forward);
	scene->has_camera = 1;
}

void	parse_light(t_scene *scene, char **parts)
{
	int	i;

	i = scene->light_count;
	scene->lights[i].origin = parse_vec3(parts[1]);
	scene->lights[i].brightness = ft_atof(parts[2]);
	scene->lights[i].color = parse_color(parts[3]);
	scene->light_count++;
}
