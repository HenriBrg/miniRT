/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldoldlights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 16:35:23 by henri             #+#    #+#             */
/*   Updated: 2020/01/25 15:21:01 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int	apply_ambient(t_ambiant_light *ambient, int colour)
{
	t_rgb	obj_rgb;
	t_rgb	amb_rgb;
	t_rgb	output;

	decode_rgb(colour, &obj_rgb.r, &obj_rgb.g, &obj_rgb.b);
	decode_rgb(ambient->colour, &amb_rgb.r, &amb_rgb.g, &amb_rgb.b);
	output.r = obj_rgb.r * ((amb_rgb.r / 255) * ambient->ratio);
	output.g = obj_rgb.g * ((amb_rgb.g / 255) * ambient->ratio);
	output.b = obj_rgb.b * ((amb_rgb.b / 255) * ambient->ratio);
	return ((((output.r << 8) + output.g) << 8) + output.b);
}

/*
** Peu importe le point d'intersection pour le plane / square / triangle,
** la normale sera toujours la même
** https://www.scratchapixel.com/lessons/3d-basic-rendering/
** introduction-to-shading/shading-normals
*/

double	getincidence(t_interobject *object, t_vector3 dirphoton, t_vector3 hit)
{
	double		incidence;
	t_vector3	normal;

	if (object->type == SPHERE)
		normal = getnormalsphere((t_sphere*)(object->ptr), hit);
	else if (object->type == PLANE)
		normal = ((t_plane*)(object->ptr))->normal;
	else if (object->type == SQUARE)
		normal = ((t_square*)(object->ptr))->normal;
	else if (object->type == TRIANGLE)
		normal = getnormaltriangle((t_triangle*)(object->ptr));
	else if (object->type == CYLINDER)
		normal = getnormalcylinder((t_cylinder*)(object->ptr), hit);
	else
		return (-1);
	incidence = dot(norm(normal), dirphoton);
	return (incidence);
}

int		illuminate(t_light *light, double incidence, int colour)
{
	t_rgb	obj_rgb;
	t_rgb	light_rgb;
	t_rgb	output;

	decode_rgb(colour, &obj_rgb.r, &obj_rgb.g, &obj_rgb.b);
	decode_rgb(light->colour, &light_rgb.r, &light_rgb.g, &light_rgb.b);
	output.r = obj_rgb.r + (incidence * ((light_rgb.r / 255) * light->ratio));
	output.g = obj_rgb.g + (incidence * ((light_rgb.g / 255) * light->ratio));
	output.b = obj_rgb.b + (incidence * ((light_rgb.b / 255) * light->ratio));
	// output.r = (output.r > 255) ? 255 : output.r;
	// output.g = (output.g > 255) ? 255 : output.g;
	// output.b = (output.b > 255) ? 255 : output.b;
	return ((((output.r << 8) + output.g) << 8) + output.b);
}

/*
** Description
** Si obstacle.inter = FALSE alors la lumière ne rencontre donc aucun obstacle
** et elle impact la couleur du pixel / de l'objet issu de la fonction raytrace()
** Dans ce cas on calcul l'incidence, mais le calcul varie selon l'objet
*/

void 	lighting(t_data *data, t_interobject *object, t_camera *cam, t_vector3 ray)
{
	double			incidence;
	t_light			*light;
	t_vector3		hit;
	t_vector3		dirphoton;
	t_interobject	obstacle;

	light = data->lights;
	hit = getpointfromray(cam->pos, ray, object->distance);
	while (light != NULL)
	{
		dirphoton = norm(subvec(light->pos, hit));
		obstacle = intersearch(data, light->pos, dirphoton);
		if (obstacle.inter == FALSE)
		{
			incidence = getincidence(object, dirphoton, hit);
			if (incidence >= 0 && incidence <= 1)
				object->colour = illuminate(light, incidence, object->colour);
		}
		light = light->next;
	}
}
