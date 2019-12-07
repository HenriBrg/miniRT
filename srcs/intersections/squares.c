/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:17:47 by henri             #+#    #+#             */
/*   Updated: 2019/12/07 19:20:23 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*

int solve_square_boundaries(t_rt_param *param, t_square *square)
{
	t_vector3	point;
	double		x_proj;
	double		z_proj;

	point = point_from_ray(param->origin, param->ray, param->i);
	point = direction_vector(point, square->centre);
	x_proj = dot(point, square->x) / square->height;
	z_proj = dot(point, square->z) / square->height;
	if ((x_proj < square->height && x_proj > 0) &&
		(z_proj < square->height && z_proj > 0))
		return (1);
	return (0);
}

t_vector3 point_from_ray(t_vector3 origin, t_vector3 ray, double t)
{
	origin.x += ray.x * t;
	origin.y += ray.y * t;
	origin.z += ray.z * t;
	return (origin);
}
*/

/*
** Point représente le vecteur qui depuis la caméra, touche le point
** d'intersections sur le square
** La ligne suivante : point = subvec(square->center, point);
** va donner le vecteur depuis le centre allant vers le point d'intersection
*/

t_vector3 direction_vector(t_vector3 a, t_vector3 b)
{
	b.x -= a.x;
	b.y -= a.y;
	b.z -= a.z;
	return (b);
}

t_vector3 point_from_ray(t_vector3 origin, t_vector3 ray, double t)
{
	origin.x += ray.x * t;
	origin.y += ray.y * t;
	origin.z += ray.z * t;
	return (origin);
}

static int	squarebounds(t_square *square, t_camera *cam, t_vector3 ray, double t)
{
	double x;
	double z;
	t_vector3 point;

	// point.x = cam->pos.x + (ray.x * t);
	// point.y = cam->pos.y + (ray.y * t);
	// point.z = cam->pos.z + (ray.z * t);
	// point.x = square->center.x - point.x;
	// point.y = square->center.y - point.y;
	// point.z = square->center.z - point.z;
	point = point_from_ray(cam->pos, ray, t);
	point = direction_vector(point, square->center);
	x = scalar(point, square->x) / square->height;
	z = scalar(point, square->z) / square->height;
	// printf("xproj = %lf et yprof = %lf\n",x, z);
	if ((x > 0 && x < square->height) && (z > 0 && z < square->height))
	{
		//printf("T = %lf\n", t);
		//printf("RAY(%lf, %lf, %lf)\n",ray.x, ray.y, ray.z);

		//printf("Point(%lf, %lf, %lf)\n",point.x, point.y, point.z);
		return (1);

	}
	return (0);
}

static double intersquares(t_square *square, t_camera *cam, t_vector3 ray)
{
	double 	t;
	double	denom;

	t = scalar(subvec(square->center, cam->pos), square->normal);
	denom = scalar(ray, square->normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (-1);
	t = t / denom;
	//printf("t = %lf\n", t);
	if (t > 0 && (squarebounds(square, cam, ray, t) == 1))
		return (t);
	return (-1);
}

void try_squares(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj)
{
	double tmp;
	double inter;
	t_square *square;

	tmp = -1;
	inter = -1;
	square = data->squares;
	while (square != NULL)
	{
		tmp = intersquares(square, cam, ray);
		// if (tmp != -1)
		// 	printf("InterSquare = %lf\n", tmp);
		if (tmp != -1 && ((inter != -1 && tmp < inter) || (inter == -1)))
		{
			inter = tmp;
			obj->inter = TRUE;
			obj->ray = ray;
			obj->origin = cam->pos;
			obj->ptr = (t_square*)square;
			obj->distance = tmp;
			obj->colour = square->colour;
		}
		square = square->next;
	}
}
