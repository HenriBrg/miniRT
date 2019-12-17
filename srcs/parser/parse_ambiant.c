/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambiant.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:31:55 by henri             #+#    #+#             */
/*   Updated: 2019/12/17 18:09:02 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	parse_ambiant(t_data *data, char **tab)
{
	if (ft_strslen(tab) != 3)
		corrupted(data, tab, "Bad ambiant format");
	if (double_format(tab[1]) == -1 || rgb_format(tab[2]) == -1)
		corrupted(data, tab, "Bad ambiant format");
	if (!(data->amb = malloc(sizeof(t_ambiant_light))))
		corrupted(data, tab, "Can't malloc ambiant light");
	data->amb->ratio = ft_atod(tab[1]);
	data->amb->colour = str_to_rgb(tab[2]);
}
