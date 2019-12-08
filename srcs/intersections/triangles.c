/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 23:19:39 by henri             #+#    #+#             */
/*   Updated: 2019/12/08 23:26:50 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_vector3 getnormaltriangle()

double	intertriangle(t_triangle *triangle, t_camera *cam, t_vector3 ray)
{

}

void try_triangles(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj)
{
	double tmp;
	double inter;
	t_triangle *triangle;

	tmp = -1;
	inter = -1;
	triangle = data->triangles;
	while (triangle != NULL)
	{
		tmp = intertriangle(triangle, cam, ray);
		if (tmp != -1 && ((inter != -1 && tmp < inter) || (inter == -1)))
		{
			inter = tmp;
			obj->inter = TRUE;
			obj->ray = ray;
			obj->origin = cam->pos;
			obj->ptr = (t_triangle*)triangle;
			obj->distance = tmp;
			obj->colour = triangle->colour;
		}
		triangle = triangle->next;
	}
}
