/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:09:38 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 23:18:22 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
** http://www.iquilezles.org/www/articles/intersectors/intersectors.htm
*/

static double		intercylinder(t_cylinder *cyl, t_camera *cam, t_vector3 ray)
{
	t_vector3		ca;
	t_vector3		oc;
	t_vector3		abc;
	t_vector3		hty;
	t_vector3		cardoc;

	ca = subvec(cyl->pb, cyl->center);
	oc = subvec(cam->pos, cyl->center);
	cardoc.x = dotsame(ca);
	cardoc.y = dot(ca, ray);
	cardoc.z = dot(ca, oc);
	abc.x = cardoc.x - (cardoc.y * cardoc.y);
	abc.y = cardoc.x * dot(oc, ray) - (cardoc.z * cardoc.y);
	abc.z = cardoc.x * dotsame(oc) - (cardoc.z * cardoc.z)
			- (cyl->radius * cyl->radius * cardoc.x);
	hty.x = (abc.y * abc.y) - (abc.x * abc.z);
	if (hty.x < 0)
		return (-1);
	hty.x = sqrt(hty.x);
	hty.y = (-abc.y - hty.x) / abc.x;
	hty.z = cardoc.z + (hty.y * cardoc.y);
	if (hty.z > 0 && hty.z < cardoc.x)
		return (hty.y);
	hty.y = (((hty.z < 0) ? 0 : cardoc.x) - cardoc.z) / cardoc.y;
	return ((((fabs(abc.y + (abc.x * hty.y)) < hty.x) && hty.y > 0)) ? hty.y : -1);
}


void			try_cylinders(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj)
{
	double 		tmp;
	double 		inter;
	t_cylinder 	*cylinder;

	tmp = -1;
	inter = -1;
	cylinder = data->cylinders;
	while (cylinder != NULL)
	{
		tmp = intercylinder(cylinder, cam, ray);
		if (tmp != -1 && ((tmp < obj->distance) || (obj->inter == 0)))
		{
			inter = tmp;
			obj->inter = TRUE;
			obj->ray = ray;
			obj->origin = cam->pos;
			obj->ptr = (t_cylinder*)cylinder;
			obj->distance = tmp;
			obj->colour = cylinder->colour;
		}
		cylinder = cylinder->next;
	}
}
