/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:34:31 by hberger           #+#    #+#             */
/*   Updated: 2020/01/25 20:13:17 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int		getblue(int colour)
{
	return (colour & 0xFF);
}

int		getgreen(int colour)
{
	return ((colour & 0xFF00) >> 8);
}

int		getred(int colour)
{
	return ((colour & 0xFF0000) >> 16);
}

int		encodergb(int red, int green, int blue)
{
	return ((((red << 8) + green) << 8) + blue);
}

void	decodergb(int colour, int *red, int *green, int *blue)
{
	*red = getred(colour);
	*green = getgreen(colour);
	*blue = getblue(colour);
}
