/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:31:55 by henri             #+#    #+#             */
/*   Updated: 2019/12/26 19:06:35 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	parse_ambiant(t_data *data, char **tab, int fd)
{
	if (data->parse_amb_doublon != 0)
		corrupted(data, tab, "Ambiant declared twice", fd);
	data->parse_amb_doublon = 1;
	if (ft_strslen(tab) != 3)
		corrupted(data, tab, "Bad ambiant format (too many args)", fd);
	if (ft_atod(tab[1]) < 0 || ft_atod(tab[1]) > 1)
		corrupted(data, tab, "Bad ambiant intensity", fd);
	if (double_format(tab[1]) == -1 || rgb_format(tab[2]) == -1)
		corrupted(data, tab, "Bad ambiant format (double or rgb)", fd);
	if (!(data->amb = malloc(sizeof(t_ambiant_light))))
		corrupted(data, tab, "Can't malloc ambiant light", fd);
	data->amb->ratio = ft_atod(tab[1]);
	data->amb->colour = str_to_rgb(tab[2]);
}
