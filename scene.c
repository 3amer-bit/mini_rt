#include <math.h>
#include "vector.h"
#include "scene.h"

static t_camera	setup_camera(void)
{
	t_camera	cam;
	t_vec3		world_up;

	world_up = (t_vec3){0, 1, 0};
	cam.origin = (t_point3){0, 0, 1};
	cam.forward = (t_vec3){0, 0, -1};
	cam.right = normalize(cross(cam.forward, world_up));
	cam.up = cross(cam.right, cam.forward);
	cam.fov = 80;
	cam.scale = tan(degrees_to_radians(cam.fov) * 0.5);
	return (cam);
}

t_scene	init_scene(void)
{
	t_scene	scene;

	scene.camera = setup_camera();
	scene.ambient_light.color = (t_color){0, 1, 1, 1};
	scene.ambient_light.brightness = 0.5;
	scene.light.brightness = 0.9;
	scene.light.origin = (t_point3){1, 1, 1};
	scene.light.direction = (t_point3){-1, -1, -1};
	scene.objects[0].origin = (t_point3){0, 0, -1};
	scene.objects[0].radius = 0.5;
	scene.objects[0].mat.albedo = (t_color){1, 1, 0, 0};
	scene.objects[1].origin = (t_point3){0, -100.5, -1};
	scene.objects[1].radius = 100;
	scene.objects[1].mat.albedo = (t_color){1, 1, 0, 0};
	scene.obj_count = 1;
	return (scene);
}
