/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 23:01:44 by henri             #+#    #+#             */
/*   Updated: 2019/11/28 15:06:12 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*
** On pose l'équation suivante : ax^2 + bx + c avec x correspondant à t période
** L'équation de la sphère : x^2+y^2+z^2=Rayon^2
** Il existe une combinaison de points pour lesquels cette équation est vraie
** Ces points désigne la surface de la sphère, centrée à l'origine et rayon R
** Soit P cette combinaison de point, alors on aura P^2 - R^2 = 0
** Tout est très bien expliqué sur ce lien :
** https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
*/

int	intersphere(t_data *data, t_camera *cam, t_vector3 ray)
{
	double	a;
	double	b;
	double	c;
	double	x1;
	double	x2;
	double	delta;

	a = scalar(ray, ray);
	b = 2 * scalar(ray, subvec(cam->pos, data->spheres->center));
	c = scalar(subvec(cam->pos, data->spheres->center), subvec(cam->pos, data->
	spheres->center)) - (data->spheres->radius * (data->spheres->radius / 4));
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (0);
	else if (delta == 0)
	{
		x1 = -b / (2 * a);
		return (1);
	}
	else
	{
		x1 = (-b - sqrt(delta)) / (2 * a);
		x2 = (-b + sqrt(delta)) / (2 * a);
		return (1);
	}
}
