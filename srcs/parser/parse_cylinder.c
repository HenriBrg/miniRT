/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:07 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 23:19:28 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
cy 	50.0,0.0,20.6 	0.0,0.0,1.0 	10,0,255 	14.2 	21.42
*/

t_cylinder		*parse_cylinder(t_data *data, char **tab, int fd)
{
	t_vector3	center;
	t_vector3	orient;
	t_cylinder	*cylinder;

	if (ft_strslen(tab) != 6)
		corrupted(data, tab, "Bad cylinder format (too many args)", fd);
	if (vec3_format(tab[1], &center) == -1)
		corrupted(data, tab, "Bad cylinder position format", fd);
	if (vec3_format(tab[2], &orient) == -1)
		corrupted(data, tab, "Bad cylinder orient format", fd);
	if (check_range_vec3_orient(&orient) == -1)
		corrupted(data, tab, "cylinder orient not in range [-1;1]", fd);
	if (double_format(tab[3]) == -1 || double_format(tab[4]) == -1)
		corrupted(data, tab, "Bad cylinder radius or height format", fd);
	if (rgb_format(tab[5]) == -1)
		corrupted(data, tab, "Bad cylinder rgb format", fd);
	if (!(cylinder = malloc(sizeof(t_cylinder))))
		corrupted(data, tab, "Can't malloc cylinder", fd);
	cylinder->next = NULL;
	cylinder->center = center;
	cylinder->orientation = reorientate(newvec(0,1,0), orient);
	cylinder->radius = ft_atod(tab[3]) / 2;
	cylinder->height = ft_atod(tab[4]);
	cylinder->colour = str_to_rgb(tab[5]);
	cylinder->pb = addvec(center,
						   mult1vec(cylinder->orientation, cylinder->height));
	return (cylinder);
}

void			free_cylinder(t_data *data)
{
	t_cylinder 	*tmp;
	t_cylinder 	*next;

	tmp = data->cylinders;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void			add_cylinder(t_data *data, char **tab, int fd)
{
	t_cylinder	*tmp;

	if (data->cylinders == 0)
		data->cylinders = parse_cylinder(data, tab, fd);
	else
	{
		tmp = data->cylinders;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_cylinder(data, tab, fd);
	}
}
