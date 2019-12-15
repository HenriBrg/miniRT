/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:14:50 by henri             #+#    #+#             */
/*   Updated: 2019/12/15 15:01:14 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	solvequadratic(t_vector3 abc, double *t0, double *t1)
{
	double	tmp;
	double	delta;

	if ((delta = pow(abc.y, 2) - 4 * abc.x * abc.z) < 0)
		return (-1);
	if (delta == 0)
	{
		*t0 = -abc.y / (2 * abc.x);
		return (1);
	}
	*t0 = (-abc.y - sqrt(delta)) / (2 * abc.x);
	*t1 = (-abc.y + sqrt(delta)) / (2 * abc.x);
	tmp = *t0;
	if (*t0 > *t1)
	{
		*t0 = *t1;
		*t1 = tmp;
	}
	return (2);
}
