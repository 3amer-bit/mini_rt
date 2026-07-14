/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 13:48:18 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/30 13:48:19 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

static int	intersects_anything(t_ray ray, t_scene scene, double max_dist)
{
	int		i;
	t_hit	hit;

	i = 0;
	while (i < scene.obj_count)
	{
		hit = scene.objects[i].intersect(&ray, scene.objects[i].data);
		if (hit.t > EPSILON && hit.t < max_dist)
			return (1);
		i++;
	}
	return (0);
}

int	in_shadow(t_hit hit, t_scene scene, t_light light)
{
	t_ray	shadow_ray;
	t_vec3	light_vec;
	double	dist_to_light;

	light_vec = sub(light.origin, hit.point);
	dist_to_light = vec_len(light_vec);
	shadow_ray.origin = hit.point;
	shadow_ray.direction = normalize(light_vec);
	return (intersects_anything(shadow_ray, scene, dist_to_light + EPSILON));
}

t_vec3	reflect(t_vec3 normal, t_vec3 light_dir)
{
	return (sub(light_dir, scale(normal, 2 * dot(light_dir, normal))));
}
