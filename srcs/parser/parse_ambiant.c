/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:31:55 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 22:28:05 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	parse_ambiant(t_data *data, char **tab, int fd)
{
	t_ambiant_light *ambiant;

	if (data->parse_amb_doublon != 0)
		corrupted(data, tab, "Ambiant declared twice", fd);
	data->parse_amb_doublon = 1;
	if (ft_strslen(tab) != 3)
		corrupted(data, tab, "Bad ambiant format (too many args)", fd);
	if (double_format(tab[1]) == -1 || rgb_format(tab[2]) == -1)
		corrupted(data, tab, "Bad ambiant format (double or rgb)", fd);
	if (!(ambiant = malloc(sizeof(t_ambiant_light))))
		corrupted(data, tab, "Can't malloc ambiant light", fd);
	ambiant->ratio = ft_atod(tab[1]);
	ambiant->colour = str_to_rgb(tab[2]);
	data->amb = ambiant;
}
