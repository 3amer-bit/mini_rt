/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:55:54 by aalemami          #+#    #+#             */
/*   Updated: 2026/07/10 19:36:26 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	valid_num_str(const char *s, int allow_dot)
{
	int	i;
	int	digits;
	int	dots;

	i = 0;
	digits = 0;
	dots = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] == '.' && allow_dot)
			dots++;
		else if (s[i] >= '0' && s[i] <= '9')
			digits++;
		else
			return (0);
		i++;
	}
	return (digits > 0 && dots <= 1);
}

void	check_argc(t_scene *scene, char **parts, int expected)
{
	int	i;

	i = 0;
	while (parts && parts[i])
		i++;
	if (i != expected)
		ft_error(scene, "Wrong number of fields on a line");
}

void	check_number(t_scene *scene, const char *s)
{
	if (!s || !valid_num_str(s, 1))
		ft_error(scene, "Invalid number format");
}
