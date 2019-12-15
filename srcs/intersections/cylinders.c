/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:09:38 by henri             #+#    #+#             */
/*   Updated: 2019/12/15 15:51:01 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"


static int check_cyl_solve(t_rt_param *param, t_cylindre *cyl)
{
	t_vector3	d_x_t;
	t_vector3	abc;
	int 		sol;

	d_x_t.x = dot(param->ray, cyl->orient);
	d_x_t.y = dot(sub_vect(param->origin, cyl->centre), cyl->orient);
	abc.x = dot_same(param->ray) - pow(d_x_t.x, 2);
	abc.y = 2 * (dot(param->ray, sub_vect(param->origin, cyl->centre)) -
			d_x_t.x * d_x_t.y);
	abc.z = dot_same(sub_vect(param->origin, cyl->centre)) -
			pow(d_x_t.y, 2) - pow(cyl->diametre / 2, 2);
	sol = solve_quadratic(abc, &(param->i), &(param->i_2));
	if (sol >= 1)
		param->v = 1;
	if (sol == 2)
		param->v_2 = 1;
	return (sol);
}

int	raytrace_cyl(t_rt_param *param)
{
	t_cylindre	*cyl;
	double		h1;
	double		h2;

	cyl = param->object;
	if (!check_cyl_solve(param, cyl))
		return (0);
	h1 = dot(sub_vect(param->origin, cyl->centre), cyl->orient) +
		dot(param->ray, cyl->orient) * param->i;
	if (h1 < 0 || h1 > cyl->height)
		param->v = 0;
	h2 = dot(sub_vect(param->origin, cyl->centre), cyl->orient) +
		dot(param->ray, cyl->orient) * param->i_2;
	if (h2 < 0 || h2 > cyl->height)
		param->v_2 = 0;
	return ((param->v && h1 < cyl->height) ||
			(param->v_2 && h2 < cyl->height));
}

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
