/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 21:09:32 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/29 11:46:31 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "scene.h"

# define EPSILON 1e-6
# define PI 3.1415926535897932385

typedef struct s_framebuffer
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_framebuf;

typedef struct s_pixel
{
	int		x;
	int		y;
	t_color	color;
}	t_pixel;

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_framebuf	*framebuf;
	t_scene		scene;
	int			width;
	int			height;
	int			redraw;
}	t_window;

int		handle_keypress(int keysym, t_window *data);
int		handle_destroy_structure_notify(t_window *data);
int		loop_hook(t_window *data);
void	mlx_destroy(t_window *win_ctx);
void	ft_mlx_put_pixel(t_framebuf *framebuf, t_pixel *pixel);
double	degrees_to_radians(double degrees);
void	render(t_framebuf *framebuf, t_scene scene);

// parsing

double	ft_atof(const char *s);
t_vec3	parse_vec3(t_scene *scene, char *s);
t_color	parse_color(t_scene *scene, char *s);
void	parse_ambient(t_scene *scene, char **parts);
void	parse_camera(t_scene *scene, char **parts);
void	parse_light(t_scene *scene, char **parts);
void	parse_sphere(t_scene *scene, char **parts);
void	parse_plane(t_scene *scene, char **parts);
void	parse_cylinder(t_scene *scene, char **parts);
t_scene	parse_scene(char *filename);
void	ft_error(t_scene *scene, char *msg);
void	free_scene(t_scene *scene);
void	free_parts(char **parts);

// validation

int		valid_num_str(const char *s, int allow_dot);
void	check_argc(t_scene *scene, char **parts, int expected);
void	check_number(t_scene *scene, const char *s);
void	check_int(t_scene *scene, const char *s);
void	check_range(t_scene *scene, double val, double min, double max);
void	check_positive(t_scene *scene, double val);
void	check_nonzero_vec(t_scene *scene, t_vec3 v);
void	set_default_material(t_material *mat);
double	parse_ratio(t_scene *scene, char *s);
t_vec3	parse_direction(t_scene *scene, char *s);
double	parse_pos_num(t_scene *scene, char *s);

// cylinder

double	cy_axial(t_ray *ray, t_cylinder *cy, double t);
t_vec3	cy_body_normal(t_ray *ray, t_cylinder *cy, double t);

#endif