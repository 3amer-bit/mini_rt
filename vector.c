#include <math.h>
#include "scene.h"
#include "minirt.h"
#include "vector.h"

t_vec3	scale(t_vec3 vec, double scaler)
{
	return ((t_vec3){
		vec.x * scaler,
		vec.y * scaler,
		vec.z * scaler
	});
}

double	dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3	sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec3	normalize(t_vec3 v)
{
	double	length;
	double	inv_length;

	length = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	if (length > EPSILON)
	{
		inv_length = 1 / length;
		v.x *= inv_length;
		v.y *= inv_length;
		v.z *= inv_length;
	}
	return (v);
}
