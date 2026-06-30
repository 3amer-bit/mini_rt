/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:55:11 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/30 13:50:12 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vector.h"
#include "scene.h"
#include "minirt.h"

static double	cy_body_t(t_ray *ray, t_cylinder *cy)
{
	t_vec3	rd;
	t_vec3	od;
	double	coeff[3];
	double	disc;
	double	t;

	rd = sub(ray->direction,
			scale(cy->normal, dot(ray->direction, cy->normal)));
	od = sub(sub(ray->origin, cy->origin), scale(cy->normal,
				dot(sub(ray->origin, cy->origin), cy->normal)));
	coeff[0] = dot(rd, rd);
	coeff[1] = 2.0 * dot(rd, od);
	coeff[2] = dot(od, od) - cy->radius * cy->radius;
	disc = coeff[1] * coeff[1] - 4.0 * coeff[0] * coeff[2];
	if (coeff[0] < EPSILON || disc < 0.0)
		return (-1.0);
	t = (-coeff[1] - sqrt(disc)) / (2.0 * coeff[0]);
	if (t <= EPSILON || fabs(cy_axial(ray, cy, t)) > cy->height / 2.0)
		t = (-coeff[1] + sqrt(disc)) / (2.0 * coeff[0]);
	if (t <= EPSILON || fabs(cy_axial(ray, cy, t)) > cy->height / 2.0)
		return (-1.0);
	return (t);
}

static double	cy_cap_t(t_ray *ray, t_point3 center,
						t_vec3 axis, double radius)
{
	double		t;
	double		denom;
	t_point3	point;

	denom = dot(ray->direction, axis);
	if (fabs(denom) < EPSILON)
		return (-1.0);
	t = dot(sub(center, ray->origin), axis) / denom;
	if (t <= EPSILON)
		return (-1.0);
	point = add(ray->origin, scale(ray->direction, t));
	if (vec_len(sub(point, center)) > radius)
		return (-1.0);
	return (t);
}

static t_hit	cy_fill_hit(t_ray *ray, t_cylinder *cy, double t, t_vec3 normal)
{
	t_hit	hit;

	hit.t = t;
	hit.point = add(ray->origin, scale(ray->direction, t));
	hit.normal = normal;
	if (dot(ray->direction, hit.normal) > 0)
		hit.normal = scale(hit.normal, -1.0);
	hit.view_dir = scale(ray->direction, -1.0);
	hit.mat = &cy->mat;
	return (hit);
}

static int	cy_is_best(double *t, int idx)
{
	int	i;

	if (t[idx] <= EPSILON)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (i != idx && t[i] > EPSILON && t[i] < t[idx])
			return (0);
		i++;
	}
	return (1);
}

t_hit	intersect_cylinder(t_ray *ray, void *obj)
{
	t_cylinder	*cy;
	t_hit		miss;
	double		t[3];

	cy = (t_cylinder *) obj;
	t[0] = cy_body_t(ray, cy);
	t[1] = cy_cap_t(ray, sub(cy->origin, scale(cy->normal, cy->height / 2.0)),
			cy->normal, cy->radius);
	t[2] = cy_cap_t(ray, add(cy->origin, scale(cy->normal, cy->height / 2.0)),
			cy->normal, cy->radius);
	if (cy_is_best(t, 0))
		return (cy_fill_hit(ray, cy, t[0], cy_body_normal(ray, cy, t[0])));
	if (cy_is_best(t, 1))
		return (cy_fill_hit(ray, cy, t[1], scale(cy->normal, -1.0)));
	if (cy_is_best(t, 2))
		return (cy_fill_hit(ray, cy, t[2], cy->normal));
	miss = (t_hit){0};
	miss.t = -1.0;
	return (miss);
}
