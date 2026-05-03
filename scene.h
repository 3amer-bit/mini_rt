#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_vec3	t_point3;

typedef struct s_amb
{
	t_color	color;
	double	brightness;
}	t_amb;

typedef struct s_light
{
	t_point3	origin;
	t_vec3		direction;
	double		brightness;
}	t_light;

typedef struct s_camera
{
	t_point3	origin;
	t_vec3		forward;
	t_vec3		up;
	t_vec3		right;
	double		fov;
	double		scale;
}	t_camera;

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray;

typedef struct s_material
{
	t_color	albedo;
	double	reflectivity;
	double	roughness;
}	t_material;

typedef struct s_sphere
{
	t_point3	origin;
	double		radius;
	t_material	mat;
}	t_sphere;

typedef struct s_hit
{
	double		t;
	t_point3	point;
	t_vec3		normal;
	t_material	*mat;
}	t_hit;

typedef struct s_object
{
	void	*data;
	t_hit	(*intersect)(t_ray *, void *);
}	t_object;

typedef struct s_scene
{
	t_amb		ambient_light;
	t_camera	camera;
	// TODO ADD LIGHTS
	t_light		light;
	// t_sphere	objects[100]
	t_sphere	objects[100];
	int			obj_count;
}	t_scene;

t_hit	intersect_sphere(t_ray *ray, t_sphere *sphere);
t_scene	init_scene(void);
void	render(t_framebuf *framebuf, t_scene scene);

#endif