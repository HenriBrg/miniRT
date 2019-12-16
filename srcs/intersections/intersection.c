/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 23:01:44 by henri             #+#    #+#             */
/*   Updated: 2019/12/15 19:41:14 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_interobject intersearch(t_data *data, t_camera *cam, t_vector3 ray)
{
	t_interobject	object;

	object.inter = FALSE;
	object.ray = newvec(0, 0, 0);
	object.origin = newvec(0, 0, 0);
	object.ptr = 0;
	object.colour = 0;
	object.distance = 0;
	object.intercount = 0;
	object.t0 = 0;
	object.t1 = 0;

	try_spheres(data, cam, ray, &object);
	try_planes(data, cam, ray, &object);
	try_squares(data, cam, ray, &object);
	try_triangles(data, cam, ray, &object);
	try_cylinders(data, cam, ray, & object);
	return (object);
}
