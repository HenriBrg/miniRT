/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:09:38 by henri             #+#    #+#             */
/*   Updated: 2019/12/16 20:26:19 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
static void	solvable(t_cylinder *cylinder, t_camera *cam, t_vector3 ray, t_interobject *obj)
{
	double		x;
	double		y;
	t_vector3	abc;

	x = dot(ray, cylinder->orientation);
	y = dot(subvec(cam->pos, cylinder->center), cylinder->orientation);
	abc.x = dotsame(ray) - pow(x, 2);
	abc.y = 2 * dot(ray, subvec(cam->pos, cylinder->center)) - (x * y);
	abc.z = dotsame(subvec(cam->pos, cylinder->center))
		- pow(y, 2) - pow(cylinder->diameter / 2, 2);
	obj->intercount = solvequadratic(abc, &obj->t0, &obj->t1);
}

static double	intercylinder(t_cylinder *cylinder, t_camera *cam, t_vector3 ray, t_interobject *obj)
{
	int		tmp;
	double	a;
	double	b;

	tmp = 1;
	solvable(cylinder, cam, ray, obj);
	//printf("Intercount = %d avec t0 = %lf et t1 = %lf\n", obj->intercount, obj->t0, obj->t1);
	a = dot(subvec(cam->pos, cylinder->center), cylinder->orientation) +
		dot(ray, cylinder->orientation) * obj->t0;
	if (a < 0 || a > cylinder->height)
		obj->v = 0;
	b = dot(subvec(cam->pos, cylinder->center), cylinder->orientation) +
		dot(ray, cylinder->orientation) * obj->t1;
	if (b < 0 || b > cylinder->height)
		obj->v2 = 0;
	return ((a < cylinder->height && obj->v) ||
			(b < cylinder->height && obj->v2));
}
*/

/*
** https://mrl.nyu.edu/~dzorin/cg05/lecture12.pdf
** https://mrl.nyu.edu/~dzorin/rend05/lecture2.pdf
** http://www.iquilezles.org/www/articles/intersectors/intersectors.htm
*/

static double	intercylinder(t_cylinder *cylinder, t_camera *cam, t_vector3 ray, t_interobject *)
{
	/* VARIABLES
	v = ray
	q = ray
	qi = ray * i
	qt = ray * t
	va = cylinder->orientation
	p = cam->pos
	pa = cylinder->center
	r = radius
	p1 = bottom base center
	p2 = top base center

	// codam
	p = ray.origin;
	v = ray.direction;
	pa = cylinder.position;
	va = cylinder.rotation;
	r = cylinder.radius;
	q1 = p + v * t1;
	q2 = p + v * t1;


	t_vector3	abc;
	t_vector3	delta;

	delta = subvec(cam->pos, cylinder->center);

	abc.x = dotsame(subvec(ray, mult1vec(cylinder->orientation, dot(ray, cylinder->orientation))));

	abc.y = 2 * (dot(subvec(ray, mult1vec(cylinder->orientation,
										  dot(ray, cylinder->orientation)))),
				    (subvec(delta, mult1vec(cylinder->orientation,
						 				dot(cylinder->orientation, delta)))));


	abc.z = dotsame(subvec(delta, mult1vec(cylinder->orientation,
										  dot(delta, cylinder->orientation))))
										  - pow(cylinder->radius, 2);

	obj->intercount = solvequadratic(abc, &obj->t0, &obj->t1);
	if (obj->intercount == 0)
		return (-1);

	double inter1;
	double inter2;
	double inter3;
	double inter4;
	double botcenter;
	double topcenter;



	inter1 = dot(cylinder->orientation, subvec())
	*/
}

static double	intercylinder(t_cylinder *cylinder, t_camera *cam, t_vector3 ray)
{
	t_vector3	topbot;

	const t_vector topcenter = addvec(cylinder->center, mult1vec(cylinder->orientation, cylinder->height));

	topbot = subvec()
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
			obj->type = CYLINDER;
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
