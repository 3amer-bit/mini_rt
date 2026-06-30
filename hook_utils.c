/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/30 13:46:12 by aalemami          #+#    #+#             */
/*   Updated: 2026/06/30 13:46:16 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/Xutil.h>
#include "vector.h"
#include "minirt.h"

int	move_camera(int keysym, t_camera *cam)
{
	t_vec3	*o;

	o = &cam->origin;
	if (keysym == XK_w)
		*o = add(*o, scale(cam->forward, 0.5));
	else if (keysym == XK_s)
		*o = sub(*o, scale(cam->forward, 0.5));
	else if (keysym == XK_d)
		*o = add(*o, scale(cam->right, 0.5));
	else if (keysym == XK_a)
		*o = sub(*o, scale(cam->right, 0.5));
	else if (keysym == XK_q)
		*o = add(*o, scale(cam->up, 0.5));
	else if (keysym == XK_e)
		*o = sub(*o, scale(cam->up, 0.5));
	else
		return (0);
	return (1);
}
