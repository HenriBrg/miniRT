/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:17:47 by henri             #+#    #+#             */
/*   Updated: 2019/12/09 23:13:57 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
** Une normale correspond à un vecteur perpendiculaire à une surface
** En l'occurence, la normale d'un plan signifie le vecteur pour lequel l'angle
** formé par le vecteur et le plan est de 90°
** https://stackoverflow.com/questions/23975555/how-to-do-ray-plane-intersection
*/

double interplanes(t_plane *plane, t_camera *cam, t_vector3 ray)
{
	double x;
	double denom;

	x = dot(subvec(plane->center, cam->pos), plane->normal);
	denom = dot(ray, plane->normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (-1);
	x = x / denom;
	return ((x > 0) ? x : -1);
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
			printf("Plane intersection = %lf\n", tmp);
		}
		plane = plane->next;
	}
}
