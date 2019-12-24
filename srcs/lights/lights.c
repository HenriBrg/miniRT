/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 16:35:23 by henri             #+#    #+#             */
/*   Updated: 2019/12/24 17:57:17 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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
double	incidence(t_light *light, t_vector3 point)
{

}
*/

/*
t_interobject		obstaclesearch(t_data *data, t_light *light, t_interobject *obj, t_vector3 photon)
{
	t_interobject	obstacle;

	obstacle.inter = FALSE;
	obstacle.distance = 0;
	obstacle.ptr = 0;
	obstacle.colour = 0;

	return (obstacle);
}

void 	lighting(t_data *data, t_interobject *obj, t_camera *cam, t_vector3 ray)
{
	t_light			*light;
	t_vector3		hit;
	t_vector3		photon;

	light = data->lights;
	while (light != NULL)
	{
		hit = getpointfromray(cam, ray, obj->distance);
		photon = norm(subvec(light->pos, hit));
		obstacle = obstaclesearch(data, light, obj, photon))
		// if (obstacle.inter = TRUE)
		// 		compute light incidence and then change colour
		light = light->next;
	}
}
*/
