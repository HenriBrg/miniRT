/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 23:12:15 by henri             #+#    #+#             */
/*   Updated: 2019/12/08 23:17:06 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
** Retourne le vecteur allant du point b au point a
*/

t_vector3 getdirectionalvector(t_vector3 a, t_vector3 b)
{
	b.x -= a.x;
	b.y -= a.y;
	b.z -= a.z;
	return (b);
}

/*
** Retourne un vecteur qui pointe à l'endroit pile de l'intersection
*/

t_vector3 getpointfromray(t_vector3 origin, t_vector3 ray, double t)
{
	origin.x += ray.x * t;
	origin.y += ray.y * t;
	origin.z += ray.z * t;
	return (origin);
}
