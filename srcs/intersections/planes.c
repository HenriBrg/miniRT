/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:17:47 by henri             #+#    #+#             */
/*   Updated: 2020/01/25 15:19:56 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double		interplanes(t_plane *plane, t_vector3 pov, t_vector3 ray)
{
	double	t;
	double	denom;

	t = dot(subvec(plane->center, pov), plane->normal);
	denom = dot(ray, plane->normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (-1);
	t = t / denom;
	if (t > 0)
		return (t);
	return (-1);
}

void		try_planes(t_data *data, t_vector3 pov, t_vector3 ray,
	t_interobject *obj)
{
	double	tmp;
	double	inter;
	t_plane	*plane;

	tmp = -1;
	inter = -1;
	plane = data->planes;
	while (plane != NULL)
	{
		tmp = interplanes(plane, pov, ray);
		if (tmp != -1 && ((tmp < obj->distance) || (obj->inter == 0)))
		{
			inter = tmp;
			obj->inter = TRUE;
			obj->distance = tmp;
			obj->type = PLANE;
			obj->ptr = (t_plane*)plane;
			obj->colour = plane->colour;
		}
		plane = plane->next;
	}
}
