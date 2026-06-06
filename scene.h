#ifndef SCENE_H
# define SCENE_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_color;

typedef struct s_amb
{
	t_color	color;
	double	brightness;
}	t_amb;

typedef struct s_light
{
	t_point3	origin;
	t_color		color;
	double		brightness;
}	t_light;

typedef struct s_camera
{
	t_point3	origin;
	t_vec3		forward;
	t_vec3		up;
	t_vec3		right;
	double		fov;
}	t_camera;

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray;

typedef struct s_material
{
	t_color	albedo;
	double	diffuse;
	double	specular;
	double	shininess;
}	t_material;

typedef struct s_sphere
{
	t_point3	origin;
	double		radius;
	t_material	mat;
}	t_sphere;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
	t_material	mat;
}	t_plane;

typedef struct s_hit
{
	double		t;
	t_point3	point;
	t_vec3		normal;
	t_vec3		view_dir;
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
	t_light		lights[100];
	t_object	objects[100];
	int			obj_count;
	int			light_count;
	int			has_ambient;
	int			has_camera;
}	t_scene;

//cylinder

typedef struct s_cylinder
{
	t_point3	origin;
	t_vec3		normal;
	double		radius;
	double		height;
	t_material	mat;
}	t_cylinder;

t_hit	intersect_sphere(t_ray *ray, void *obj);
t_hit	intersect_plane(t_ray *ray, void *obj);
t_hit	intersect_cylinder(t_ray *ray, void *obj);
t_scene	init_scene(void);
int		in_shadow(t_hit hit, t_scene scene, t_light light);
t_vec3	reflect(t_vec3 normal, t_vec3 light_dir);
t_color	shade(t_hit hit, t_scene scene);

#endif