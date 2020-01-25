/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:53:39 by henri             #+#    #+#             */
/*   Updated: 2020/01/25 15:20:13 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

double		veclen(t_vector3 vec)
{
	double	len;

	len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (len);
}

double		dot(t_vector3 vec1, t_vector3 vec2)
{
	double	dot;

	dot = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (dot);
}

double		dotsame(t_vector3 vec1)
{
	double	ret;

	ret = dot(vec1, vec1);
	return (ret);
}

t_vector3	addvec(t_vector3 vec1, t_vector3 vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);
}
