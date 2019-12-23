/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 16:35:23 by henri             #+#    #+#             */
/*   Updated: 2019/12/23 19:13:51 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	apply_ambient(t_ambiant_light *ambient, int colour)
{
	t_rgb	obj_rgb;
	t_rgb	amb_rgb;
	t_rgb	output;

	decode_rgb(colour, &obj_rgb.r, &obj_rgb.g, &obj_rgb.b);
	decode_rgb(ambient->colour, &amb_rgb.r, &amb_rgb.g, &amb_rgb.b);
	output.r = obj_rgb.r * ((amb_rgb.r / 255) * ambient->ratio);
	output.g = obj_rgb.g * ((amb_rgb.g / 255) * ambient->ratio);
	output.b = obj_rgb.b * ((amb_rgb.b / 255) * ambient->ratio);
	return ((((output.r << 8) + output.g) << 8) + output.b);
}
