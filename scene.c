#include "vector.h"
#include "scene.h"

static t_camera	setup_camera(void)
{
	t_camera	cam;
	t_vec3		world_up;

	world_up = (t_vec3){0, 1, 0};
	cam.origin = (t_point3){0.0, 1.0, 2.0};
	cam.forward = normalize((t_vec3){0.0, -0.1, -1.0});
	cam.right = normalize(cross(cam.forward, world_up));
	cam.up = cross(cam.right, cam.forward);
	cam.fov = 60;
	return (cam);
}

t_scene	init_scene(void)
{
	t_scene	scene;

	scene = (t_scene){0};
	scene.camera = setup_camera();
	scene.ambient_light.color = (t_color){0.6, 0.7, 1.0};
	scene.ambient_light.brightness = 0.15;
	scene.lights[0] = (t_light){
		.origin = {-2.5, 2.0, 2.0},
		.color = {1.0, 0.95, 0.85},
		.brightness = 0.9
	};
	scene.lights[1] = (t_light){
		.origin = {2.5, 1.0, 1.5},
		.color = {0.6, 0.7, 1.0},
		.brightness = 0.5
	};
	scene.light_count = 2;
	static t_sphere	spheres[] = {
	{
		.origin = {0, 0, -1},
		.radius = 0.5,
		.mat = {
		.albedo = {0.9, 0.2, 0.2},
		.diffuse = 0.7,
		.specular = 0.4,
		.shininess = 64}
	},
	{
		.origin = {-1.2, 0, -1.2},
		.radius = 0.5,
		.mat = {
		.albedo = {0.2, 0.8, 0.3},
		.diffuse = 0.9,
		.specular = 0.1,
		.shininess = 8
	}
	},
	{
		.origin = {1.2, 0, -1.2},
		.radius = 0.5,
		.mat = {
		.albedo = {0.2, 0.3, 0.9},
		.diffuse = 0.6,
		.specular = 0.6,
		.shininess = 128}
	},
	{
		.origin = {0, -100.5, -1},
		.radius = 100,
		.mat = {
		.albedo = {0.8, 0.8, 0.8},
		.diffuse = 0.95,
		.specular = 0.05,
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
	scene.obj_count = 4;
	return (scene);
}
