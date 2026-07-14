/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:58:12 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"

void	parse_sphere(t_scene *scene, char **parts)
{
	t_sphere	sp;
	t_sphere	*sp_ptr;

	check_argc(scene, parts, 4);
	if (scene->obj_count >= 100)
		ft_error(scene, "Too many objects");
	sp.origin = parse_vec3(scene, parts[1]);
	sp.radius = parse_pos_num(scene, parts[2]) / 2.0;
	sp.mat.albedo = parse_color(scene, parts[3]);
	set_default_material(&sp.mat);
	sp_ptr = malloc(sizeof(t_sphere));
	if (!sp_ptr)
		ft_error(scene, "Memory allocation failed");
	*sp_ptr = sp;
	scene->objects[scene->obj_count].data = sp_ptr;
	scene->objects[scene->obj_count].intersect = intersect_sphere;
	scene->obj_count++;
}

void	parse_plane(t_scene *scene, char **parts)
{
	t_plane	pl;
	t_plane	*pl_ptr;

	check_argc(scene, parts, 4);
	if (scene->obj_count >= 100)
		ft_error(scene, "Too many objects");
	pl.point = parse_vec3(scene, parts[1]);
	pl.normal = parse_direction(scene, parts[2]);
	pl.mat.albedo = parse_color(scene, parts[3]);
	set_default_material(&pl.mat);
	pl_ptr = malloc(sizeof(t_plane));
	if (!pl_ptr)
		ft_error(scene, "Memory allocation failed");
	*pl_ptr = pl;
	scene->objects[scene->obj_count].data = pl_ptr;
	scene->objects[scene->obj_count].intersect = intersect_plane;
	scene->obj_count++;
}

void	parse_cylinder(t_scene *scene, char **parts)
{
	t_cylinder	cy;
	t_cylinder	*cy_ptr;

	check_argc(scene, parts, 6);
	if (scene->obj_count >= 100)
		ft_error(scene, "Too many objects");
	cy.origin = parse_vec3(scene, parts[1]);
	cy.normal = parse_direction(scene, parts[2]);
	cy.radius = parse_pos_num(scene, parts[3]) / 2.0;
	cy.height = parse_pos_num(scene, parts[4]);
	cy.mat.albedo = parse_color(scene, parts[5]);
	set_default_material(&cy.mat);
	cy_ptr = malloc(sizeof(t_cylinder));
	if (!cy_ptr)
		ft_error(scene, "Memory allocation failed");
	*cy_ptr = cy;
	scene->objects[scene->obj_count].data = cy_ptr;
	scene->objects[scene->obj_count].intersect = intersect_cylinder;
	scene->obj_count++;
}
