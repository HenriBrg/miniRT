/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:26:10 by hberger           #+#    #+#             */
/*   Updated: 2020/01/25 20:15:03 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double				vecangles(t_vector3 a, t_vector3 b)
{
	double			d;
	double			angle;
	t_vector3		tmp;

	tmp = newvec(0, 0, 0);
	d = dot(a, b) / (distance(a, tmp) * distance(b, tmp));
	angle = acos(d);
	return (angle);
}

t_vector3			getnormalvector(t_interobject *object, t_vector3 hit,
	t_vector3 ray)
{
	t_vector3		normal;

	if (object->type == SPHERE)
		normal = getnormalsphere((t_sphere*)(object->ptr), hit);
	else if (object->type == PLANE)
		normal = ((t_plane*)(object->ptr))->normal;
	else if (object->type == SQUARE)
		normal = ((t_square*)(object->ptr))->normal;
	else if (object->type == TRIANGLE)
		normal = getnormaltriangle((t_triangle*)(object->ptr));
	else
		normal = getnormalcylinder((t_cylinder*)(object->ptr), hit);
	if (dot(normal, ray) > 0)
		normal = mult1vec(normal, -1.0);
	return (norm(normal));
}

double				getincidence(t_light *light, t_interobject *object,
	t_camera *cam, t_vector3 ray)
{
	t_vector3		hit;
	t_vector3		normal;
	t_vector3		tmp;
	t_vector3		photon;
	double			incidence;

	tmp = newvec(0, 0, 0);
	hit = getpointfromray(cam->pos, ray, object->distance);
	normal = getnormalvector(object, hit, ray);
	photon = subvec(light->pos, hit);
	incidence = dot(normal, photon);
	incidence /= (distance(normal, tmp) * distance(photon, tmp));
	incidence = acos(incidence);
	return (incidence);
}

int					obstruction(t_data *data, t_interobject *object,
	t_light *light, t_vector3 ray)
{
	t_vector3		hit;
	t_vector3		photon;
	t_interobject	obstacle;

	hit = getpointfromray(get_current_camera(data)->pos, ray, object->distance);
	photon = norm(subvec(light->pos, hit));
	hit = addvec(hit, mult1vec(getnormalvector(object, hit, ray), 0.001));
	obstacle = intersearch(data, hit, photon);
	if (obstacle.inter && obstacle.distance >= 0)
		if (distance(hit, light->pos) > distance(hit,
			getpointfromray(hit, photon, obstacle.distance)))
			return (1);
	return (0);
}

int					lighting(t_data *data, t_interobject *object, t_camera *cam,
	t_vector3 ray)
{
	t_light			*light;
	int				finalcolor;
	int				tmpcolor;
	double			incidence;

	finalcolor = 0;
	light = data->lights;
	while (light != NULL)
	{
		if (obstruction(data, object, light, ray) == 0)
		{
			incidence = getincidence(light, object, cam, ray);
			if (incidence < M_PI_2 && incidence > -M_PI_2)
			{
				tmpcolor = intensity(light->colour, sin(M_PI_2 - incidence));
				finalcolor = addlights(finalcolor, tmpcolor);
			}
		}
		light = light->next;
	}
	finalcolor = addlights(finalcolor, data->amb->colour);
	finalcolor = filtercolors(finalcolor, object->colour);
	return (finalcolor);
}
