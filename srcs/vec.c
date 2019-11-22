/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:53:39 by henri             #+#    #+#             */
/*   Updated: 2019/11/22 23:55:30 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_vector3 newvec(double x, double y, double z)
{
	t_vector3 new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

double veclen(t_vector3 vec)
{
	double len;

	len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (len);
}

t_vector3 norm(t_vector3 vec)
{
	double len;

	len = veclen(vec);
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vector3 multvec(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3 new;

	new.x = vec1.x * vec2.x;
	new.y = vec1.y * vec2.y;
	new.z = vec1.z * vec2.z;
	return (new);
}

double dot(t_vector3 vec1, t_vector3 vec2)
{
	double dot;

	dot = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (dot);
}

t_vector3 subvec(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3 new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	new.z = vec1.z - vec2.z;
	return (new);
}

double rad(double degree)
{
	return (degree * M_PI / 180.0);
}
