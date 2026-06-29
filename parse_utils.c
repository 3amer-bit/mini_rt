/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:57:50 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/29 00:00:00 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft/inc/libft.h"

static double	parse_fraction(const char *s)
{
	double	fraction;
	double	power;

	fraction = 0.0;
	power = 1.0;
	while (*s >= '0' && *s <= '9')
	{
		fraction = fraction * 10.0 + (*s++ - '0');
		power *= 10.0;
	}
	return (fraction / power);
}

double	ft_atof(const char *s)
{
	double	result;
	int		sign;

	result = 0.0;
	sign = 1;
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		result = (result * 10) + (*s++ - '0');
	if (*s == '.')
		result += parse_fraction(s + 1);
	return (sign * result);
}

t_vec3	parse_vec3(t_scene *scene, char *s)
{
	char	**p;
	t_vec3	v;

	p = ft_split(s, ',');
	if (!p || !p[0] || !p[1] || !p[2] || p[3])
	{
		free_parts(p);
		ft_error(scene, "Wrong number of fields on a line");
	}
	if (!valid_num_str(p[0], 1) || !valid_num_str(p[1], 1)
		|| !valid_num_str(p[2], 1))
	{
		free_parts(p);
		ft_error(scene, "Invalid number format");
	}
	v = (t_vec3){ft_atof(p[0]), ft_atof(p[1]), ft_atof(p[2])};
	free_parts(p);
	return (v);
}

void	ft_error(t_scene *scene, char *msg)
{
	int	r;

	if (scene)
	{
		if (scene->cur_parts)
			free_parts(scene->cur_parts);
		if (scene->cur_line)
			free(scene->cur_line);
		free_scene(scene);
	}
	r = write(2, "Error\n", 6);
	r = write(2, msg, ft_strlen(msg));
	r = write(2, "\n", 1);
	(void)r;
	exit(1);
}
