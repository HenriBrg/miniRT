/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squares.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:17:47 by henri             #+#    #+#             */
/*   Updated: 2020/01/22 17:03:33 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

// t_vector3	getnormalsquare(t_square *square)
// {
// 	return (square->normal);
// }

/*
** Point représente le vecteur qui depuis la caméra, touche le point
** d'intersections sur le square
** La ligne suivante : point = subvec(square->center, point);
** va donner le vecteur depuis le centre allant vers le point d'intersection
//printf("T = %lf\n", t);
//printf("RAY(%lf, %lf, %lf)\n",ray.x, ray.y, ray.z);
// printf("xproj = %lf et yprof = %lf\n",x, z);
//printf("Point(%lf, %lf, %lf)\n",point.x, point.y, point.z);
*/

static int	squarebounds(t_square *square, t_vector3 pov, t_vector3 ray, double t)
{
	double x;
	double z;
	t_vector3 point;

	point = getpointfromray(pov, ray, t);
	point = subvec(square->center, point);
	x = dot(point, square->x) / square->height;
	z = dot(point, square->z) / square->height;
	if ((x > 0 && x < square->height) && (z > 0 && z < square->height))
		return (1);
	return (0);
}

static double intersquares(t_square *square, t_vector3 pov, t_vector3 ray)
{
	double 	t;
	double	denom;

	t = dot(subvec(square->center, pov), square->normal);
	denom = dot(ray, square->normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (-1);
	t = t / denom;
	if (t > 0 && (squarebounds(square, pov, ray, t) == 1))
		return (t);
	return (-1);
}

void try_squares(t_data *data, t_vector3 pov, t_vector3 ray, t_interobject *obj)
{
	double tmp;
	double inter;
	t_square *square;

	tmp = -1;
	inter = -1;
	square = data->squares;
	while (square != NULL)
	{
		tmp = intersquares(square, pov, ray);
		if (tmp != -1 && ((tmp < obj->distance) || (obj->inter == 0)))
		{
			inter = tmp;
			obj->inter = TRUE;
			obj->distance = tmp;
			obj->type = SQUARE;
			obj->ptr = (t_square*)square;
			obj->colour = square->colour;
		}
		square = square->next;
	}
}
