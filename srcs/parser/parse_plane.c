/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:13 by henri             #+#    #+#             */
/*   Updated: 2020/01/25 15:20:30 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_plane			*parse_plane(t_data *data, char **tab, int fd)
{
	t_vector3	pos;
	t_vector3	normal;
	t_plane		*plane;

	if (ft_strslen(tab) != 4)
		corrupted(data, tab, "Bad plane format (too many args)", fd);
	if (vec3_format(tab[1], &pos) == -1)
		corrupted(data, tab, "Bad plane position format", fd);
	if (vec3_format(tab[2], &normal) == -1)
		corrupted(data, tab, "Bad plane normal format", fd);
	if (check_range_vec3_orient(&normal) == -1)
		corrupted(data, tab, "plane normal not in range [-1;1]", fd);
	if (rgb_format(tab[3]) == -1)
		corrupted(data, tab, "Bad plane rgb format", fd);
	if (!(plane = malloc(sizeof(t_plane))))
		corrupted(data, tab, "Can't malloc plane", fd);
	plane->center = pos;
	plane->next = NULL;
	plane->normal = reorientate(newvec(0, 1, 0), normal);
	plane->colour = str_to_rgb(tab[3]);
	return (plane);
}

void			free_plane(t_data *data)
{
	t_plane		*tmp;
	t_plane		*next;

	tmp = data->planes;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void			add_plane(t_data *data, char **tab, int fd)
{
	t_plane		*tmp;

	if (data->planes == 0)
		data->planes = parse_plane(data, tab, fd);
	else
	{
		tmp = data->planes;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_plane(data, tab, fd);
	}
}
