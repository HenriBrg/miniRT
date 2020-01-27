/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergecolors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 19:40:00 by hberger           #+#    #+#             */
/*   Updated: 2020/01/27 14:24:50 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int			intensity(int colour, double ratio)
{
	int		r;
	int		g;
	int		b;

	decodergb(colour, &r, &g, &b);
	r = (double)r * ratio;
	g = (double)g * ratio;
	b = (double)b * ratio;
	return (encodergb(r, g, b));
}

int			addlights(int a, int b)
{
	t_rgb	l_a;
	t_rgb	l_b;

	decodergb(a, &(l_a.r), &(l_a.g), &(l_a.b));
	decodergb(b, &(l_b.r), &(l_b.g), &(l_b.b));
	l_a.r += l_b.r;
	l_a.g += l_b.g;
	l_a.b += l_b.b;
	if (l_a.r > 255)
		l_a.r = 255;
	if (l_a.g > 255)
		l_a.g = 255;
	if (l_a.b > 255)
		l_a.b = 255;
	return (encodergb(l_a.r, l_a.g, l_a.b));
}

int			filtercolors(int source, int colour)
{
	t_rgb	src;
	t_rgb	surf;

	decodergb(source, &(src.r), &(src.g), &(src.b));
	decodergb(colour, &(surf.r), &(surf.g), &(surf.b));
	if (surf.r > src.r)
		surf.r = src.r;
	if (surf.g > src.g)
		surf.g = src.g;
	if (surf.b > src.b)
		surf.b = src.b;
	return (encodergb(surf.r, surf.g, surf.b));
}
