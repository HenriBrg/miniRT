/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:17:47 by henri             #+#    #+#             */
/*   Updated: 2019/12/15 14:59:54 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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

double	intersphere(t_sphere *sphere, t_camera *cam, t_vector3 ray)
{
	double		t0;
	double		t1;
	t_vector3	abc;

	t0 = -1;
	abc.x = dot(ray, ray);
	abc.y = 2 * dot(ray, subvec(cam->pos, sphere->center));
	abc.z = dot(subvec(cam->pos, sphere->center),
			subvec(cam->pos, sphere->center)) -
			(sphere->radius * (sphere->radius / 4));
	solvequadratic(abc, &t0, &t1);
	return (t0);
}

/*
** ATTENTION : problème lorsque deux sphères se trouvent à la même distance de la caméra (c.a.d que le x du vecteur est identique)
** les pixels se chevauchent incorrectement !
*/

void try_spheres(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj)
{
	double tmp;
	double inter;
	t_sphere *sphere;

	tmp = -1;
	inter = -1;
	sphere = data->spheres;
	while (sphere != NULL)
	{
		tmp = intersphere(sphere, cam, ray);
		//if (tmp != -1 && ((inter != -1 && tmp < inter) || (inter == -1)))
		if (tmp != -1 && ((tmp < obj->distance) || (obj->inter == 0)))
		{
			inter = tmp;
			obj->inter = TRUE;
			obj->ray = ray;
			obj->origin = cam->pos;
			obj->ptr = (t_sphere*)sphere;
			obj->distance = tmp;
			obj->colour = sphere->colour;
			//printf("Sphere intersection = %lf\n", tmp);
		}
		sphere = sphere->next;
	}
}
