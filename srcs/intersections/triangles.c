/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 23:19:39 by henri             #+#    #+#             */
/*   Updated: 2019/12/10 12:30:59 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_vector3		getnormaltriangle(t_vector3 p1, t_vector3 p2, t_vector3 p3)
{
	t_vector3 ab;
	t_vector3 ac;

	ab = subvec(p2, p1);
	ac = subvec(p3, p1);
	return (norm(cross(ac, ab)));
}

/*
** Following this tutorial : https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
*/

static int		trianglebounds(t_triangle *triangle, t_camera *cam, t_vector3 ray, double t)
{
	t_vector3	edge;
	t_vector3	inter;
	t_vector3	normal;
	t_vector3	insidevec;

	inter = getpointfromray(cam->pos, ray, t);
	normal = getnormaltriangle(triangle->p1, triangle->p2, triangle->p3);
	insidevec = subvec(inter, triangle->p1);
	edge = subvec(triangle->p2, triangle->p1);
	if (dot(normal, cross(edge, insidevec)) > 0)
		return (0);
	edge = subvec(triangle->p3, triangle->p2);
	insidevec = subvec(inter, triangle->p2);
	if (dot(normal, cross(edge, insidevec)) > 0)
		return (0);
	edge = subvec(triangle->p1, triangle->p3);
	insidevec = subvec(inter, triangle->p3);
	if (dot(normal, cross(edge, insidevec)) > 0)
		return (0);
	return (1);
}

static double	intertriangle(t_triangle *triangle, t_camera *cam, t_vector3 ray)
{
	double		t;
	double		denom;
	t_vector3	normal;

	normal = getnormaltriangle(triangle->p1, triangle->p2, triangle->p3);
	t = dot(subvec(triangle->p1, cam->pos), normal);
	denom = dot(ray, normal);
	if (denom < 1e-8 && denom > -1 * (1e-8))
		return (-1);
	t /= denom;
	if (t > 0 && trianglebounds(triangle, cam, ray, t) == 1)
		return (t);
	return (-1);
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
		if (tmp != -1 && ((tmp < obj->distance) || (obj->inter == 0)))
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
