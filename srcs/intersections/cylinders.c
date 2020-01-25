/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:09:38 by henri             #+#    #+#             */
/*   Updated: 2020/01/25 15:19:52 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

/*
** https://mrl.nyu.edu/~dzorin/intro-graphics-f01/lectures/normals.pdf
**
** Explication car un peu inintuitive cette fonction :
** 1) height --> On calcul "en combien de longueur du vecteur orientation"
** le point d'intersection se trouve
** 2) On trace le vecteur qui va de la base jusqu'au niveau (en hauteur)
** du point d'intersection le long de l'axe d'orientation (variable tmp)
** On soustrait le point trouvé (tmp) au point d'intersection et hop on
** obtient la normale
*/

t_vector3		getnormalcylinder(t_cylinder *cylinder, t_vector3 point)
{
	double		height;
	t_vector3	tmp;

	height = dot(subvec(point, cylinder->center), cylinder->orientation);
	tmp = getpointfromray(cylinder->center, cylinder->orientation, height);
	tmp = subvec(point, tmp);
	return (tmp);
}

/*
** http://www.iquilezles.org/www/articles/intersectors/intersectors.htm
*/

double			intercylinder(t_cylinder *cyl, t_vector3 pov, t_vector3 ray)
{
	t_vector3	ca;
	t_vector3	oc;
	t_vector3	abc;
	t_vector3	hty;
	t_vector3	cardoc;

	ca = subvec(cyl->pb, cyl->center);
	oc = subvec(pov, cyl->center);
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
	if ((hty.z = cardoc.z + (hty.y * cardoc.y)) > 0 && hty.z < cardoc.x)
		return (hty.y);
	hty.y = (((hty.z < 0) ? 0 : cardoc.x) - cardoc.z) / cardoc.y;
	return ((((fabs(abc.y + (abc.x * hty.y)) < hty.x) && hty.y > 0)) ?
	hty.y : -1);
}

void			try_cylinders(t_data *data, t_vector3 pov, t_vector3 ray,
	t_interobject *obj)
{
	double		tmp;
	double		inter;
	t_cylinder	*cylinder;

	tmp = -1;
	inter = -1;
	cylinder = data->cylinders;
	while (cylinder != NULL)
	{
		tmp = intercylinder(cylinder, pov, ray);
		if (tmp != -1 && ((tmp < obj->distance) || (obj->inter == 0)))
		{
			inter = tmp;
			obj->inter = TRUE;
			obj->distance = tmp;
			obj->type = CYLINDER;
			obj->ptr = (t_cylinder*)cylinder;
			obj->colour = cylinder->colour;
		}
		cylinder = cylinder->next;
	}
}
