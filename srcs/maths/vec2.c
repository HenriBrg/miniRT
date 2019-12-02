/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:53:39 by henri             #+#    #+#             */
/*   Updated: 2019/12/02 19:17:12 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"


/*
** Retourne la longueur du vecteur : ||vec||
*/

double veclen(t_vector3 vec)
{
	double len;

	len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
	return (len);
}

/*
** Retourne le produit scalaire : A ^ B
*/

double scalar(t_vector3 vec1, t_vector3 vec2)
{
	double scalar;

	scalar = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (scalar);
}

/*
** Retourne vec1 + vec2
*/

t_vector3 addvec(t_vector3 vec1, t_vector3 vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return (vec1);
}
