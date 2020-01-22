/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:17:47 by henri             #+#    #+#             */
/*   Updated: 2020/01/22 17:03:41 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_vector3		getnormalsphere(t_sphere *sphere, t_vector3 point)
{
	return (subvec(point, sphere->center));
}


/*
** On pose l'équation suivante : ax^2 + bx + c avec x correspondant à t période
** L'équation de la sphère : x^2+y^2+z^2=Rayon^2
** Il existe une combinaison de points pour lesquels cette équation est vraie
** Ces points désigne la surface de la sphère, centrée à l'origine et rayon R
** Soit P cette combinaison de point, alors on aura P^2 - R^2 = 0
** Tout est très bien expliqué sur ce lien :
** https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
**
**
** NB : Comment faire si x1 = 0 ou quasiment ?
*/

double	intersphere(t_sphere *sphere, t_vector3 pov, t_vector3 ray)
{
	double		t0;
	double		t1;
	t_vector3	abc;

	t0 = -1;
	abc.x = dot(ray, ray);
	abc.y = 2 * dot(ray, subvec(pov, sphere->center));
	abc.z = dot(subvec(pov, sphere->center),
			subvec(pov, sphere->center)) -
			(sphere->radius * (sphere->radius / 4));
	solvequadratic(abc, &t0, &t1);
	return ((t0 > 0) ? t0 : -1);
}

/*
** ATTENTION : problème lorsque deux sphères se trouvent à la même distance de la caméra (c.a.d que le x du vecteur est identique)
** les pixels se chevauchent incorrectement !
*/

void try_spheres(t_data *data, t_vector3 pov, t_vector3 ray, t_interobject *obj)
{
	double tmp;
	double inter;
	t_sphere *sphere;

	tmp = -1;
	inter = -1;
	sphere = data->spheres;
	while (sphere != NULL)
	{
		tmp = intersphere(sphere, pov, ray);
		if (tmp != -1 && ((tmp < obj->distance) || (obj->inter == 0)))
		{
			inter = tmp;
			obj->inter = TRUE;
			obj->type = SPHERE;
			obj->distance = tmp;
			obj->ptr = (t_sphere*)sphere;
			obj->colour = sphere->colour;
		}
		sphere = sphere->next;
	}
}
