/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:08:38 by henri             #+#    #+#             */
/*   Updated: 2019/12/17 19:33:37 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	parse_resolution(t_data *data, char **tab)
{
	printf("%s / %s / %s / %s\n", tab[0], tab[1], tab[2], tab[3]);
	if (ft_strslen(tab) != 3)
		corrupted(data, tab, "Bad resolution format (too many args)");
	if (uint_format(tab[1]) == -1 || uint_format(tab[2]) == -1)
		corrupted(data, tab, "Bad resolution format");
	if (!(data->res = malloc(sizeof(t_resolution))))
		corrupted(data, tab, "Can't malloc");
	data->res->width = ft_atoi(tab[1]);
	data->res->height = ft_atoi(tab[1]);
	if (data->res->width == 0 || data->res->height == 0)
		corrupted(data, tab, "Resolution too small");
}
