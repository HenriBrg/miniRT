/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 10:04:06 by henri             #+#    #+#             */
/*   Updated: 2020/01/20 15:17:54 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int		intensity(t_light *light, double ratio)
{
	int	r;
	int	g;
	int	b;

	decode_rgb(light->colour, &r, &g, &b);
	r = (double)r * ratio;
	g = (double)g * ratio;
	b = (double)b * ratio;
	return ((((r << 8) + g) << 8) + b);
}

int		addlights(int a, int b)
{
	t_rgb	col1;
	t_rgb	col2;

	decode_rgb(a, &(col1.r), &(col1.g), &(col1.b));
	decode_rgb(b, &(col2.r), &(col2.g), &(col2.b));
	col1.r += col2.r;
	col1.g += col2.g;
	col1.b += col2.b;
	col1.r = (col1.r > 255) ? 255 : col1.r;
	col1.g = (col1.g > 255) ? 255 : col1.g;
	col1.b = (col1.b > 255) ? 255 : col1.b;
	return ((((col1.r << 8) + col1.g) << 8) + col1.b);
}

int		filtercolors(int a, int b)
{
	t_rgb	col1;
	t_rgb	col2;

	decode_rgb(a, &(col1.r), &(col1.g), &(col1.b));
	decode_rgb(b, &(col2.r), &(col2.g), &(col2.b));
	col1.r = (col1.r > 255) ? 255 : col1.r;
	col1.g = (col1.g > 255) ? 255 : col1.g;
	col1.b = (col1.b > 255) ? 255 : col1.b;
	return ((((col1.r << 8) + col1.g) << 8) + col1.b);
}



double	getincidence(t_interobject *object, t_vector3 camray, t_vector3 photon, t_vector3 hit)
{
	t_vector3	normal;
	double		incidence;

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
	if (dot(normal, camray) > 0)
		normal = mult1vec(normal, -1.0);
	normal = norm(normal);
	incidence = dot(normal, photon) / (veclen(normal) * veclen(photon));
	incidence = acos(incidence);
	return (incidence);
}

// TODO : gérer l'évolution de la light à mesure que les autres lights passent dessus

int	checkdistance(t_interobject *obstacle, t_light *light, t_vector3 photon)
{
	t_vector3	obstacleray;
	double		dist_from_light_to_object_hit;
	double		dist_from_light_to_obstacle_hit;

	if (obstacle->inter == FALSE)
		return (FALSE);
	dist_from_light_to_object_hit = veclen(photon);
	obstacleray = getpointfromray(light->pos, norm(photon), obstacle->distance);
	dist_from_light_to_obstacle_hit = veclen(subvec(light->pos, obstacleray));
	if (dist_from_light_to_obstacle_hit > dist_from_light_to_object_hit)
		return (TRUE);
	return (FALSE);
}

void 	lighting(t_data *data, t_interobject *object, t_camera *cam, t_vector3 ray)
{
	int				tmplightcolor;
	int				lightcolor;
	double			incidence;
	t_light			*light;
	t_vector3		hit;
	t_vector3		photon;
	t_interobject	obstacle;

	light = data->lights;
	hit = getpointfromray(cam->pos, ray, object->distance);
	while (light != NULL)
	{
		photon = subvec(light->pos, hit);
		obstacle = intersearch(data, light->pos, norm(photon));
		if (obstacle.inter == FALSE || checkdistance(&obstacle, light, photon) == TRUE)
		{
			incidence = getincidence(object, ray, photon, hit);
			if (incidence < M_PI_2 && incidence > -M_PI_2)
			{
				tmplightcolor = intensity(light, sin(M_PI_2 - incidence));
				lightcolor = addlights(lightcolor, tmplightcolor);
			}
		}
		light = light->next;
	}
	// final_light = addlights(final_light, data->amb->colour);
	// final_light = filtercolors(final_light, object->colour));
	object->colour = lightcolor;
}
