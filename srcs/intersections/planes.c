/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:17:47 by henri             #+#    #+#             */
/*   Updated: 2019/12/04 20:42:31 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
** Une normale correspond à un vecteur perpendiculaire à une surface
** En l'occurence, la normale d'un plan signifie le vecteur pour lequel l'angle
** formé par le vecteur et le plan est de 90°
*/

double interplanes(t_plane *plane, t_camera *cam, t_vector3 ray)
{
	double x1;
	double denom;

	x1 = scalar(subvec(plane->center, cam->origin), plane->normal);
	denom = dot(ray, plane->normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (-1);
	x1 = x1 / denom;

}

void try_planes(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj)
{
	double tmp;
	double inter;
	t_plane *plane;

	tmp = -1;
	inter = -1;
	plane = data->planes;
	while (plane != NULL)
	{
		tmp = interplanes(plane, cam, ray);
		if (tmp != -1 && ((inter != -1 && tmp < inter) || (inter == -1)))
		{
			inter = tmp;
			obj->inter = TRUE;
			obj->ray = ray;
			obj->origin = cam->pos;
			obj->ptr = (t_plane*)plane;
			obj->distance = tmp;
			obj->colour = plane->colour;
		}
		plane = plane->next;
	}
}
