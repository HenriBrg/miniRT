/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hberger <hberger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 23:22:07 by hberger           #+#    #+#             */
/*   Updated: 2019/12/23 01:46:22 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	colorize(char *pixels, int colour, int position_on_line)
{
	pixels[0 + position_on_line * 4] = (char)((colour & 0xFF));
	pixels[1 + position_on_line * 4] = (char)((colour & 0xFF00) >> 8);
	pixels[2 + position_on_line * 4] = (char)((colour & 0xFF0000) >> 16);
}

// int apply_ambiant(t_ambiant_light *ambiant, int obj_colour)
// {
// 	int	r;
// 	int g;
// 	int b;
//
// 	r = (obj_colour & 0xFF);
// 	g = ((obj_colour & 0xFF00) >> 8);
// 	b = ((obj_colour & 0xFF0000) >> 16);
// }
