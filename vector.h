#ifndef VECTOR_H
# define VECTOR_H

# include "minirt.h"

t_vec3	sub(t_vec3 a, t_vec3 b);
double	dot(t_vec3 a, t_vec3 b);
t_vec3	normalize(t_vec3 v);
t_vec3	scale(double scaler, t_vec3 vec);
t_vec3	add(t_vec3 a, t_vec3 b);

#endif