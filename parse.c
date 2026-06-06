/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:35:59 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/06 12:59:28 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/inc/libft.h"
#include "get_next_line/get_next_line.h"
#include "minirt.h"

static void	dispatch(t_scene *scene, char **parts)
{
	if (ft_strncmp(parts[0], "A", 2) == 0)
		parse_ambient(scene, parts);
	else if (ft_strncmp(parts[0], "C", 2) == 0)
		parse_camera(scene, parts);
	else if (ft_strncmp(parts[0], "L", 2) == 0)
		parse_light(scene, parts);
	else if (ft_strncmp(parts[0], "sp", 3) == 0)
		parse_sphere(scene, parts);
	else if (ft_strncmp(parts[0], "pl", 3) == 0)
		parse_plane(scene, parts);
	else if (ft_strncmp(parts[0], "cy", 3) == 0)
		parse_cylinder(scene, parts);
	else
		ft_error("Unknown identifier");
}

static void	free_parts(char **parts)
{
	int	i;

	i = 0;
	while (parts[i])
		free(parts[i++]);
	free(parts);
}

static void	parse_line(t_scene *scene, char *line)
{
	char	**parts;

	if (line[0] == '\n' || line[0] == '\0')
		return ;
	parts = ft_split(line, ' ');
	if (!parts || !parts[0])
		return ;
	dispatch(scene, parts);
	free_parts(parts);
}

t_scene	parse_scene(char *filename)
{
	t_scene	scene;
	char	*line;
	int		fd;

	scene = (t_scene){0};
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_error("Could not open file");
	line = get_next_line(fd);
	while (line)
	{
		parse_line(&scene, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!scene.has_ambient)
		ft_error("Missing ambient light");
	if (!scene.has_camera)
		ft_error("Missing camera");
	return (scene);
}
