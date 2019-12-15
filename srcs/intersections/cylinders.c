/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:09:38 by henri             #+#    #+#             */
/*   Updated: 2019/12/15 15:54:27 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"




static int	solvable(t_cylinder *cylinder, t_camera *cam, t_vector3 ray, t_interobject *obj)
{
	double	x;
	double	y;
	double	t0;
	double	t1;
	t_vector3	abc;

	x = dot(ray, cylinder->orientation);
	y = dot(subvec(cam->pos, cylinder->center), cylinder->orientation);
	abc.x = dotsame(ray) - pow(x, 2);
	abc.y = 2 * dot(ray, subvec(cam->pos, cylinder->center)) - (x * y);
	abc.z = dotsame(subvec(cam->pos, cylinder->center))
		- pow(y, 2) - pow(cylinder->diameter / 2, 2);
	return (solvequadratic(abc, &obj->t0, &obj->t1));
}

static double	intercylinder(t_cylinder *cylinder, t_camera *cam, t_vector3 ray, t_interobject *obj)
{
	if ((obj->intercount = solvable(cylinder, cam, ray, obj)) == 0)
		return (-1);

}

void try_cylinders(t_data *data, t_camera *cam, t_vector3 ray, t_interobject *obj)
{
	double tmp;
	double inter;
	t_cylinder *cylinder;

	tmp = -1;
	inter = -1;
	cylinder = data->cylinders;
	while (cylinder != NULL)
	{
		tmp = intercylinder(cylinder, cam, ray, obj);
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
