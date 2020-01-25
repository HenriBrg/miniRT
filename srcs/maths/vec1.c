/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:53:39 by henri             #+#    #+#             */
/*   Updated: 2020/01/25 15:20:11 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

/*
** Retourne un nouveau vecteur 3D
*/

t_vector3		newvec(double x, double y, double z)
{
	t_vector3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

/*
** Retourne un nouveau vecteur 3D résultant de la soustraction de vec1 et vec2
*/

t_vector3		subvec(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3	new;

	new.x = vec1.x - vec2.x;
	new.y = vec1.y - vec2.y;
	new.z = vec1.z - vec2.z;
	return (new);
}

/*
** Multiplie le vecteur par le second paramètre et retourne un nouveau vecteur
*/

t_vector3		mult1vec(t_vector3 vec, double x)
{
	vec.x *= x;
	vec.y *= x;
	vec.z *= x;
	return (vec);
}

/*
** Multiplie deux vecteurs et retourne un nouveau vecteur
*/

t_vector3		mult2vec(t_vector3 vec1, t_vector3 vec2)
{
	t_vector3	new;

	new.x = vec1.x * vec2.x;
	new.y = vec1.y * vec2.y;
	new.z = vec1.z * vec2.z;
	return (new);
}

/*
** Normalise les vecteur, c'est à dire divise chaque valeur par la longueur
** du vecteur. On obtiendra un vecteur de longueur 1
*/

t_vector3		norm(t_vector3 vec)
{
	double		len;

	len = veclen(vec);
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}
