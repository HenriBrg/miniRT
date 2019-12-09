/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:19:04 by hberger           #+#    #+#             */
/*   Updated: 2019/12/09 21:10:20 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/*
** Applique une rotation sur l'axe x, y et z au
** vecteur d'orientation de la camera
** A la sortie au obtient un répère 3D avec
** data->cameras->vecx : RAYX --> (1.000000, 0.000000, 0.000000)
** data->cameras->vecy : RAYY --> (0.000000, 1.000000, 0.000000)
** data->cameras->vecz : RAYZ --> (0.000000, 0.000000, 1.000000)
printf("RAYX --> (%lf, %lf, %lf)\n", data->cameras->vecx.x, data->cameras->vecx.y, data->cameras->vecx.z);
printf("RAYY --> (%lf, %lf, %lf)\n", data->cameras->vecy.x, data->cameras->vecy.y, data->cameras->vecy.z);
printf("RAYZ --> (%lf, %lf, %lf)\n", data->cameras->vecz.x, data->cameras->vecz.y, data->cameras->vecz.z);
*/

t_vector3 reorientate(t_vector3 base, t_vector3 orientation)
{
	t_vector3	new;
	double		tmp;
	double		angle;

	angle = orientation.x * M_PI;
	new.x = base.x;
	new.y = base.y * cos(angle) - base.z * sin(angle);
	new.z = base.y * sin(angle) + base.z * cos(angle);
	angle = orientation.y * M_PI;
	tmp = new.x * cos(angle) + new.z * sin(angle);
	new.z = -new.x * sin(angle) + new.z * cos(angle);
	new.x = tmp;
	angle = orientation.z * M_PI;
	tmp = new.x * cos(angle) - new.y * sin(angle);
	new.y = new.x * sin(angle) + new.y * cos(angle);
	new.x = tmp;
	// printf("current ray : |%10.6g|%10.6g|%10.6g|\n", new.x, new.y, new.z);
	return (new);
}
