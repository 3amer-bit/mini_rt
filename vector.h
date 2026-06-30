/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 02:15:53 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/30 02:15:53 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "scene.h"

double	vec_len(t_vec3 v);
double	dot(t_vec3 a, t_vec3 b);
t_vec3	normalize(t_vec3 v);
t_vec3	cross(t_vec3 a, t_vec3 b);
t_vec3	scale(t_vec3 vec, double scaler);
t_vec3	add(t_vec3 a, t_vec3 b);
t_vec3	sub(t_vec3 a, t_vec3 b);

#endif