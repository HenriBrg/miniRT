/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 16:35:23 by henri             #+#    #+#             */
/*   Updated: 2019/12/25 23:57:26 by henri            ###   ########.fr       */
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
** Peu importe le point d'intersection pour le plane / square / triangle,
** la normale sera toujours la même
** https://www.scratchapixel.com/lessons/3d-basic-rendering/
** introduction-to-shading/shading-normals
*/

double	incidence(t_light *light, t_interobject *obstacle, t_vector3 dirphoton)
{
	double		ratio;
	t_vector3	normal;

	if (obstacle->type == SPHERE)
		normal = getnormalsphere((t_sphere*)(obstacle->ptr));
	else if (obstacle->type == PLANE)
		normal = ((t_plane*)(obstacle->ptr))->normal;
	else if (obstacle->type == SQUARE)
		normal = ((t_square*)(obstacle->ptr))->normal;
	else if (obstacle->type == TRIANGLE)
		normal = getnormaltriangle((t_triangle*)(obstacle->ptr));
	else if (obstacle->type == CYLINDER)
		normal = getnormalcylinder((t_cylinder*)(obstacle->ptr));
	ratio = dot(norm(normal), dirphoton);
	return (ratio);
}

color = ft_color_set_r(color, MIN(255, ft_color_get_r(color) + transmission * MAX(0, ft_vec3f_dot(next_ray.ray_dir, light_direction)) * ft_color_get_r(world->lights[k]->color)));
color = ft_color_set_g(color, MIN(255, ft_color_get_g(color) + transmission * MAX(0, ft_vec3f_dot(next_ray.ray_dir, light_direction)) * ft_color_get_g(world->lights[k]->color)));
color = ft_color_set_b(color, MIN(255, ft_color_get_b(color) + transmission * MAX(0, ft_vec3f_dot(next_ray.ray_dir, light_direction)) * ft_color_get_b(world->lights[k]->color)));


int		illuminate(t_light *light, double incidence, int colour)
{
	t_rgb	obj_rgb;
	t_rgb	light_rgb;
	t_rgb	output;

	decode_rgb(colour, &obj_rgb.r, &obj_rgb.g, &obj_rgb.b);
	decode_rgb(light->colour, &light_rgb.r, &light_rgb.g, &light_rgb.b);


	output.r = obj_rgb.r + (incidence * light_rgb.r);
	output.g = obj_rgb.g + (incidence * light_rgb.g);
	output.b = obj_rgb.b + (incidence * light_rgb.b);


	return ((((output.r << 8) + output.g) << 8) + output.b);
}

/*
** Description
** Si obstacle.inter = FALSE alors la lumière ne rencontre donc aucun obstacle
** et elle impact la couleur du pixel / de l'objet issu de la fonction raytrace()
** Dans ce cas on calcul l'incidence, mais le calcul varie selon l'objet
*/

void 	lighting(t_data *data, t_interobject *obj, t_camera *cam, t_vector3 ray)
{
	double			incidence;
	t_light			*light;
	t_vector3		hit;
	t_vector3		dirphoton;
	t_interobject	obstacle;

	light = data->lights;
	while (light != NULL)
	{
		hit = getpointfromray(cam->pos, ray, obj->distance);
		dirphoton = norm(subvec(light->pos, hit));
		obstacle = intersearch(data, light->pos, dirphoton);
		if (obstacle.inter = FALSE)
		{
			incidence = incidence(light, obstacle, photon);
			obj->colour = illuminate(light->color, ratio, );
		}
		light = light->next;
	}
}
