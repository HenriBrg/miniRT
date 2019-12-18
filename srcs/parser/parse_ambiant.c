/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:31:55 by henri             #+#    #+#             */
/*   Updated: 2019/12/18 19:48:39 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	parse_ambiant(t_data *data, char **tab)
{
	t_ambiant_light *ambiant;

	if (data->parse_amb_doublon != 0)
		corrupted(data, tab, "Ambiant declared twice");
	data->parse_amb_doublon = 1;
	if (ft_strslen(tab) != 3)
		corrupted(data, tab, "Bad ambiant format (too many args)");
	if (double_format(tab[1]) == -1 || rgb_format(tab[2]) == -1)
		corrupted(data, tab, "Bad ambiant format (double or rgb)");
	if (!(ambiant = malloc(sizeof(t_ambiant_light))))
		corrupted(data, tab, "Can't malloc ambiant light");
	ambiant->ratio = ft_atod(tab[1]);
	ambiant->colour = str_to_rgb(tab[2]);
	data->amb = ambiant;
}
