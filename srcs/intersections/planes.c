/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:17:47 by henri             #+#    #+#             */
/*   Updated: 2019/12/03 20:07:37 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void try_planes(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *object)
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
			object->inter = TRUE;
			object->ray = ray;
			object->origin = cam->pos;
			object->object = (t_plane*)plane;
			object->distance = tmp;
			object->colour = plane->colour;
		}
		plane = plane->next;
	}
}
