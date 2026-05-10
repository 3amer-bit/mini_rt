#include "vector.h"
#include "scene.h"

static t_camera	setup_camera(void)
{
	t_camera	cam;
	t_vec3		world_up;

	world_up = (t_vec3){0, 1, 0};
	cam.origin = (t_point3){0, 0, 4};
	cam.forward = (t_vec3){0, 0, -1};
	cam.right = normalize(cross(cam.forward, world_up));
	cam.up = cross(cam.right, cam.forward);
	cam.fov = 60;
	return (cam);
}

t_scene	init_scene(void)
{
	t_scene	scene;

	scene.camera = setup_camera();
	scene.ambient_light.color = (t_color){0.6, 0.7, 1.0};
	scene.ambient_light.brightness = 0.15;
	scene.lights[0].brightness = 0.9;
	scene.lights[0].color = (t_color){1.0, 0.95, 0.85};
	scene.lights[0].origin = (t_point3){-2.5, 2.0, 2.0};
	scene.lights[1].brightness = 0.5;
	scene.lights[1].color = (t_color){0.6, 0.7, 1.0};
	scene.lights[1].origin = (t_point3){2.5, 1.0, 1.5};
	scene.light_count = 2;
	scene.objects[0].origin = (t_point3){0, 0, -1};
	scene.objects[0].radius = 0.5;
	scene.objects[0].mat.albedo = (t_color){0.9, 0.2, 0.2};
	scene.objects[0].mat.diffuse = 0.7;
	scene.objects[0].mat.specular = 0.4;
	scene.objects[0].mat.shininess = 64;
	scene.objects[1].origin = (t_point3){-1.2, 0, -1.2};
	scene.objects[1].radius = 0.5;
	scene.objects[1].mat.albedo = (t_color){0.2, 0.8, 0.3};
	scene.objects[1].mat.diffuse = 0.9;
	scene.objects[1].mat.specular = 0.1;
	scene.objects[1].mat.shininess = 8;
	scene.objects[2].origin = (t_point3){1.2, 0, -1.2};
	scene.objects[2].radius = 0.5;
	scene.objects[2].mat.albedo = (t_color){0.2, 0.3, 0.9};
	scene.objects[2].mat.diffuse = 0.6;
	scene.objects[2].mat.specular = 0.6;
	scene.objects[2].mat.shininess = 128;
	scene.objects[3].origin = (t_point3){0, -100.5, -1};
	scene.objects[3].radius = 100;
	scene.objects[3].mat.albedo = (t_color){0.8, 0.8, 0.8};
	scene.objects[3].mat.diffuse = 0.95;
	scene.objects[3].mat.specular = 0.05;
	scene.objects[3].mat.shininess = 4;
	scene.obj_count = 4;
	return (scene);
}
