/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:26:10 by hberger           #+#    #+#             */
/*   Updated: 2020/01/20 19:47:56 by hberger          ###   ########.fr       */
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

double		magnitude(t_vector3 a)
{
	t_vector3 tmp;

	tmp.x = 0;
	tmp.y = 0;
	tmp.z = 0;
	return (distance(a, tmp));
}

double		angle_between_vectors(t_vector3 a, t_vector3 b)
{
	double	d;
	double	angle;

	d = dot(a, b) / (magnitude(a) * magnitude(b));
	angle = acos(d);
	return (angle);
}


t_vector3	getnormalvector(t_interobject *object, t_vector3 hit, t_vector3 ray)
{
	t_vector3 normal;

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

double		get_light_angle(t_light *light, t_interobject *object, t_camera *cam, t_vector3 ray)
{
	t_vector3	inter_point;
	t_vector3	norm_vect;

	inter_point = getpointfromray(cam->pos, ray, object->distance);
	norm_vect = getnormalvector(object, inter_point, ray);
	return (angle_between_vectors(norm_vect, subvec(light->pos, inter_point)));
}

int			obstruction(t_data *data, t_interobject *object, t_light *light, t_camera *cam, t_vector3 ray)
{
	t_vector3		start;
	t_vector3		light_ray;
	t_interobject	obstacle;

	start = getpointfromray(cam->pos, ray, object->distance);
	light_ray = norm(subvec(light->pos, start));
	start = addvec(start, mult1vec(getnormalvector(object, start, ray), 0.01));
	obstacle = intersearch(data, start, light_ray);
	if (obstacle.inter == TRUE)
	{
		if (obstacle.distance > 0)
			if (distance(start, light->pos) > distance(start, getpointfromray(start, light_ray, obstacle.distance)))
				return (1);
	}
	return (0);
}

void 	lighting(t_data *data, t_interobject *object, t_camera *cam, t_vector3 ray)
{
	t_light	*light;
	int		final_light;
	int		l_val;
	double	ang;

	final_light = 0;
	light = data->lights;
	while (light)
	{
		if (obstruction(data, object, light, cam, ray) == 0)
		{
			ang = get_light_angle(light, object, cam, ray);
			printf("ang = %lf et data.t = %lf\n", ang, object->distance);
			if (ang < M_PI_2 && ang > -M_PI_2)
			{
				l_val = intensity(light, sin(M_PI_2 - ang));
				final_light = addlights(final_light, l_val);
			}
		}
		light = light->next;
	}
	// final_light = addlights(final_light, data->amb->colour);
	// final_light = filtercolors(final_light, object->colour);
	object->colour = final_light;
}
