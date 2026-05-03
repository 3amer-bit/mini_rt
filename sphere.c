#include <math.h>
#include "vector.h"
#include "scene.h"
#include "minirt.h"

static double	solve_sphere_quadratic(t_ray *ray, t_sphere *sphere)
{
	t_vec3	origin;
	double	coeff[3];
	double	discriminant;
	double	sqrt_d;
	double	t;

	origin = sub(ray->origin, sphere->origin);
	coeff[0] = dot(ray->direction, ray->direction);
	coeff[1] = 2.0 * dot(origin, ray->direction);
	coeff[2] = dot(origin, origin) - (sphere->radius * sphere->radius);
	discriminant = coeff[1] * coeff[1] - 4 * coeff[0] * coeff[2];
	if (discriminant < 0)
		return (-1);
	sqrt_d = sqrt(discriminant);
	t = (-coeff[1] - sqrt_d) / (2.0 * coeff[0]);
	if (t <= EPSILON)
	{
		t = (-coeff[1] + sqrt_d) / (2.0 * coeff[0]);
		if (t <= EPSILON)
			return (-1);
	}
	return (t);
}

t_hit	intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_hit	hit;

	hit.t = solve_sphere_quadratic(ray, sphere);
	if (hit.t < 0)
		return (hit);
	hit.point = add(ray->origin, scale(ray->direction, hit.t));
	hit.normal = scale(sub(hit.point, sphere->origin), 1.0 / sphere->radius);
	hit.mat = &sphere->mat;
	return (hit);
}
