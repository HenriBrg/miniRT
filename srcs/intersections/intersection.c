/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 23:01:44 by henri             #+#    #+#             */
/*   Updated: 2019/12/26 15:21:42 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_interobject intersearch(t_data *data, t_vector3 pov, t_vector3 ray)
{
	t_interobject	object;

	object.type = UNDEFINED;
	object.inter = FALSE;
	object.distance = 0;
	object.ptr = 0;
	object.colour = 0;

	try_spheres(data, pov, ray, &object);
	try_planes(data, pov, ray, &object);
	try_squares(data, pov, ray, &object);
	try_triangles(data, pov, ray, &object);
	try_cylinders(data, pov, ray, &object);
	return (object);
}
