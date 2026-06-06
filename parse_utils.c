/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 00:26:34 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/06 13:05:06 by aalemami         ###   ########.fr       */
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
	double	fraction;
	double	power;
	int		sign;
	
	result = 0.0;
	fraction = 0.0;
	power = 1;
	sign = 1;
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
		result = (result * 10) + (*s++ - '0');
	if (*s == '.')
		result += parse_fraction(s + 1);
	return (sign * (result + (fraction / power)));
}

t_vec3	parse_vec3(char *s)
{
	char	**parts;
	t_vec3	v;

	parts = ft_split(s, ',');
	v.x = ft_atof(parts[0]);
	v.y = ft_atof(parts[1]);
	v.z = ft_atof(parts[2]);
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return (v);
}

t_color	parse_color(char *s)
{
	char	**parts;
	t_color	c;

	parts = ft_split(s, ',');
	c.x = ft_atoi(parts[0]) / 255.0;
	c.y = ft_atoi(parts[1]) / 255.0;
	c.z = ft_atoi(parts[2]) / 255.0;
	free(parts[0]);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return (c);
}

void	ft_error(char *msg)
{
	int	r;

	r = write(2, "Error\n", 6);
	r = write(2, msg, ft_strlen(msg));
	r = write(2, "\n", 1);
	(void)r;
	exit(1);
}
