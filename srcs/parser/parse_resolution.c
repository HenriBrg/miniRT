/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:08:38 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 22:31:18 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	parse_resolution(t_data *data, char **tab, int fd)
{
	if (data->parse_res_doublon != 0)
		corrupted(data, tab, "Resolution declared twice", fd);
	data->parse_res_doublon = 1;
	if (ft_strslen(tab) != 3)
		corrupted(data, tab, "Bad resolution format (too many args)", fd);
	if (uint_format(tab[1]) == -1 || uint_format(tab[2]) == -1)
		corrupted(data, tab, "Bad resolution format (x & y)", fd);
	if (!(data->res = malloc(sizeof(t_resolution))))
		corrupted(data, tab, "Can't malloc", fd);
	data->res->width = ft_atoi(tab[1]);
	data->res->height = ft_atoi(tab[2]);
	if (data->res->width <= 0 || data->res->height <= 0)
		corrupted(data, tab, "Resolution too small", fd);
}
