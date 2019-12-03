/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 23:01:44 by henri             #+#    #+#             */
/*   Updated: 2019/12/03 13:19:52 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
** On pose l'équation suivante : ax^2 + bx + c avec x correspondant à t période
** L'équation de la sphère : x^2+y^2+z^2=Rayon^2
** Il existe une combinaison de points pour lesquels cette équation est vraie
** Ces points désigne la surface de la sphère, centrée à l'origine et rayon R
** Soit P cette combinaison de point, alors on aura P^2 - R^2 = 0
** Tout est très bien expliqué sur ce lien :
** https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
*/

int	intersphere(t_sphere *sp, t_camera *cam, t_vector3 ray)
{
	double	a;
	double	b;
	double	c;
	double	x1;
	double	x2;
	double	delta;

	a = scalar(ray, ray);
	b = 2 * scalar(ray, subvec(cam->pos, sp->center));
	c = scalar(subvec(cam->pos, sp->center),
			   subvec(cam->pos, sp->center)) - (sp->radius * (sp->radius / 4));
	delta = pow(b, 2) - 4 * a * c;
	if (delta < 0)
		return (0);
	else if (delta == 0)
	{
		x1 = -b / (2 * a);
		return (1);
	}
	else
	{
		x1 = (-b - sqrt(delta)) / (2 * a);
		x2 = (-b + sqrt(delta)) / (2 * a);
		return (1);
	}
}


/*
**
** typedef struct s_interobject
** {
** 	int			id;
** 	t_vector3	ray;
** 	t_vector3	origin;
** 	void 		*object;
** }				t_interobject;
*/



void try_spheres(t_data *data, t_camera *cam, t_vector3 ray, t_interobject tab[128])
{
	int i;
	t_sphere *sp;

	i = 0;
	while (tab[i].inter == TRUE)
		i++;
	sp = data->spheres;
	while (sp != NULL)
	{
		if (intersphere(sp, cam, ray) == 1)
		{
			tab[i].inter = TRUE;
			tab[i].ray = ray;
			tab[i].origin = cam->pos;
			tab[i].object = (t_sphere*)sp;
			tab[i].distance = 10;
			tab[i].colour = 10;
			i++;
		}
		sp = sp->next;
	}
}



t_interobject intersearch(t_data *data, t_camera *cam, t_vector3 ray)
{
	int i;
	t_interobject	tab[128];

	i = -1;
	while (++i < 128)
		tab[i].inter = FALSE;
	try_spheres(data, cam, ray, tab);
	i = -1;
	while (++i < 128)
		if (tab[i].inter == TRUE)
			printf("Inter tab[%d] at distance %lf\n", i, tab[i].distance);
	// try_planes(data, cam, ray);
	// try_squares(data, cam, ray);
	// try_trianges(data, cam, ray);
	// try_cylinder(data, cam, ray);
	return (tab[0]);
}
