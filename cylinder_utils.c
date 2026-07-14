/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:55:38 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/30 02:15:48 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "scene.h"
#include "minirt.h"

double	cy_axial(t_ray *ray, t_cylinder *cy, double t)
{
	t_point3	point;

	point = add(ray->origin, scale(ray->direction, t));
	return (dot(sub(point, cy->origin), cy->normal));
}

t_vec3	cy_body_normal(t_ray *ray, t_cylinder *cy, double t)
{
	t_point3	point;
	double		m;

	point = add(ray->origin, scale(ray->direction, t));
	m = dot(sub(point, cy->origin), cy->normal);
	return (normalize(sub(point, add(cy->origin, scale(cy->normal, m)))));
}
