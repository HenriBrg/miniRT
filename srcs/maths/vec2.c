/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:53:39 by henri             #+#    #+#             */
/*   Updated: 2019/12/09 21:40:09 by henri            ###   ########.fr       */
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
** Retourne le produit scalaire : A ^ B (dot product)
*/

double dot(t_vector3 vec1, t_vector3 vec2)
{
	double dot;

	dot = vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
	return (dot);
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
