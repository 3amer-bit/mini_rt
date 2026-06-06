/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 00:40:08 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/06 12:51:48 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/inc/libft.h"
#include "minirt.h"
#include "vector.h"

void	parse_sphere(t_scene *scene, char **parts)
{
	t_sphere	*sp;

	sp = malloc(sizeof(t_sphere));
	sp->origin = parse_vec3(parts[1]);
	sp->radius = ft_atof(parts[2]) / 2.0;
	sp->mat.albedo = parse_color(parts[3]);
	sp->mat.diffuse = 0.7;
	sp->mat.specular = 0.3;
	sp->mat.shininess = 32;
	scene->objects[scene->obj_count].data = sp;
	scene->objects[scene->obj_count].intersect = intersect_sphere;
	scene->obj_count++;
}

void	parse_plane(t_scene *scene, char **parts)
{
	t_plane	*pl;

	pl = malloc(sizeof(t_plane));
	pl->point = parse_vec3(parts[1]);
	pl->normal = normalize(parse_vec3(parts[2]));
	pl->mat.albedo = parse_color(parts[3]);
	pl->mat.diffuse = 0.7;
	pl->mat.specular = 0.3;
	pl->mat.shininess = 32;
	scene->objects[scene->obj_count].data = pl;
	scene->objects[scene->obj_count].intersect = intersect_plane;
	scene->obj_count++;
}

void	parse_cylinder(t_scene *scene, char **parts)
{
	t_cylinder	*cy;

	cy = malloc(sizeof(t_cylinder));
	cy->origin = parse_vec3(parts[1]);
	cy->normal = normalize(parse_vec3(parts[2]));
	cy->radius = ft_atof(parts[3]) / 2.0;
	cy->height = ft_atof(parts[4]);
	cy->mat.albedo = parse_color(parts[5]);
	cy->mat.diffuse = 0.7;
	cy->mat.specular = 0.3;
	cy->mat.shininess = 32;
	scene->objects[scene->obj_count].data = cy;
	scene->objects[scene->obj_count].intersect = intersect_cylinder;
	scene->obj_count++;
}
