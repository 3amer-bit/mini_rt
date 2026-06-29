/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:56:56 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"
#include "vector.h"
#include "minirt.h"

static t_color	check_color_range(char **p, t_color c, t_scene *scene)
{
	if (c.x < 0.0 || c.x > 255.0 || c.y < 0.0 || c.y > 255.0
		|| c.z < 0.0 || c.z > 255.0)
	{
		free_parts(p);
		ft_error(scene, "Numeric value out of allowed range");
	}
	c.x /= 255.0;
	c.y /= 255.0;
	c.z /= 255.0;
	free_parts(p);
	return (c);
}

t_color	parse_color(t_scene *scene, char *s)
{
	char	**p;
	t_color	c;

	p = ft_split(s, ',');
	if (!p || !p[0] || !p[1] || !p[2] || p[3])
	{
		free_parts(p);
		ft_error(scene, "Wrong number of fields on a line");
	}
	if (!valid_num_str(p[0], 0) || !valid_num_str(p[1], 0)
		|| !valid_num_str(p[2], 0))
	{
		free_parts(p);
		ft_error(scene, "Invalid integer format");
	}
	c = (t_color){ft_atoi(p[0]), ft_atoi(p[1]), ft_atoi(p[2])};
	return (check_color_range(p, c, scene));
}

t_vec3	parse_direction(t_scene *scene, char *s)
{
	t_vec3	v;

	v = parse_vec3(scene, s);
	check_nonzero_vec(scene, v);
	return (normalize(v));
}

double	parse_pos_num(t_scene *scene, char *s)
{
	double	val;

	check_number(scene, s);
	val = ft_atof(s);
	check_positive(scene, val);
	return (val);
}
