/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:14:50 by henri             #+#    #+#             */
/*   Updated: 2020/01/25 15:25:36 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double			radian(double degree)
{
	return (degree * M_PI / 180.0);
}

t_vector3		getray(t_data *data, t_camera *cam, double x, double y)
{
	double		w;
	double		pixshift;
	t_vector3	basedir;
	t_vector3	ray;

	basedir = mult1vec(cam->vecx, (double)SCREENSIZE);
	w = (double)SCREENSIZE * tan(radian(cam->fov / 2)) * 2;
	pixshift = w / ((double)data->res->width - 1);
	ray = addvec(basedir, mult1vec(cam->vecz,
				((2 * (y + 0.5) - data->res->width) / 2) * pixshift));
	ray = addvec(ray, mult1vec(cam->vecy,
				((-2 * (x + 0.5) + data->res->height) / 2) * pixshift));
	ray = norm(ray);
	return (ray);
}

int				solvequadratic(t_vector3 abc, double *t0, double *t1)
{
	double		tmp;
	double		delta;

	if ((delta = pow(abc.y, 2) - 4 * abc.x * abc.z) < 0)
		return (-1);
	if (delta == 0)
	{
		*t0 = -abc.y / (2 * abc.x);
		return (1);
	}
	*t0 = (-abc.y - sqrt(delta)) / (2 * abc.x);
	*t1 = (-abc.y + sqrt(delta)) / (2 * abc.x);
	tmp = *t0;
	if (*t0 > *t1)
	{
		*t0 = *t1;
		*t1 = tmp;
	}
	return (2);
}
