#include <math.h>
#include "minirt.h"

t_vec3	scale(double scaler, t_vec3 vec)
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

t_vec3	sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec3	add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.x + b.x, a.y + b.y, a.z + b.z});
}

static double	vec_length(t_vec3 *v)
{
	return (sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z)));
}

t_vec3	normalize(t_vec3 v)
{
	double	length;
	double	inv_length;

	length = vec_length(&v);
	if (length > EPSILON)
	{
		inv_length = 1 / length;
		v.x *= inv_length;
		v.y *= inv_length;
		v.z *= inv_length;
	}
	return (v);
}
