#include "vector.h"
#include "scene.h"

static t_camera	setup_camera(void)
{
	t_camera	cam;
	t_vec3		world_up;

	world_up = (t_vec3){0, 1, 0};
	cam.origin = (t_point3){0.0, 1.2, 3.5};
	cam.forward = normalize((t_vec3){0.0, -0.15, -1.0});
	cam.right = normalize(cross(cam.forward, world_up));
	cam.up = cross(cam.right, cam.forward);
	cam.fov = 55;
	return (cam);
}

t_scene	init_scene(void)
{
	t_scene	scene;

	scene = (t_scene){0};
	scene.camera = setup_camera();
	scene.ambient_light.color = (t_color){0.65, 0.72, 1.0};
	scene.ambient_light.brightness = 0.12;
	scene.lights[0] = (t_light){
		.origin = {-3.0, 4.0, 2.0},
		.color = {1.0, 0.92, 0.82},
		.brightness = 1.0
	};
	scene.lights[1] = (t_light){
		.origin = {3.5, 1.5, 1.0},
		.color = {0.5, 0.65, 1.0},
		.brightness = 0.45
	};
	scene.light_count = 2;
	static t_sphere	spheres[] = {
	{
		.origin = {0.0, 0.0, -1.5},
		.radius = 0.6,
		.mat = {
		.albedo = {0.95, 0.25, 0.25},
		.diffuse = 0.7,
		.specular = 0.5,
		.shininess = 96}
	},
	{
		.origin = {-1.5, -0.05, -2.0},
		.radius = 0.55,
		.mat = {
		.albedo = {0.25, 0.85, 0.35},
		.diffuse = 0.92,
		.specular = 0.08,
		.shininess = 12}
	},
	{
		.origin = {1.5, 0.0, -2.0},
		.radius = 0.55,
		.mat = {
		.albedo = {0.2, 0.35, 0.95},
		.diffuse = 0.55,
		.specular = 0.75,
		.shininess = 180}
	},
	{
		.origin = {0.0, 0.9, -2.8},
		.radius = 0.3,
		.mat = {
		.albedo = {1.0, 0.85, 0.3},
		.diffuse = 0.6,
		.specular = 0.8,
		.shininess = 256}
	},
	{
		.origin = {0.0, -100.7, -1.0},
		.radius = 100.0,
		.mat = {
		.albedo = {0.82, 0.82, 0.85},
		.diffuse = 0.96,
		.specular = 0.03,
		.shininess = 4}
	}
	};
	scene.objects[0] = (t_object){
		.data = &spheres[0],
		.intersect = intersect_sphere
	};
	scene.objects[1] = (t_object){
		.data = &spheres[1],
		.intersect = intersect_sphere
	};
	scene.objects[2] = (t_object){
		.data = &spheres[2],
		.intersect = intersect_sphere
	};
	scene.objects[3] = (t_object){
		.data = &spheres[3],
		.intersect = intersect_sphere
	};
	scene.objects[4] = (t_object){
		.data = &spheres[4],
		.intersect = intersect_sphere
	};
	scene.obj_count = 5;
	return (scene);
}
