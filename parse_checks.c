/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:56:25 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "minirt.h"

void	check_range(t_scene *scene, double val, double min, double max)
{
	if (val < min || val > max)
		ft_error(scene, "Numeric value out of allowed range");
}

void	check_positive(t_scene *scene, double val)
{
	if (val <= 0.0)
		ft_error(scene, "Value must be greater than zero");
}

void	check_nonzero_vec(t_scene *scene, t_vec3 v)
{
	if (vec_len(v) < EPSILON)
		ft_error(scene, "Direction vector cannot be zero");
}

void	set_default_material(t_material *mat)
{
	mat->diffuse = 0.7;
	mat->specular = 0.3;
	mat->shininess = 32;
}

double	parse_ratio(t_scene *scene, char *s)
{
	double	val;

	check_number(scene, s);
	val = ft_atof(s);
	check_range(scene, val, 0.0, 1.0);
	return (val);
}
