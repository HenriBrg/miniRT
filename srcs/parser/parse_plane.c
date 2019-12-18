/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:13 by henri             #+#    #+#             */
/*   Updated: 2019/12/18 16:48:11 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
pl 		0.0,0.0,-10.0 		0.0,1.0,0.0 	0,0,225
typedef struct	s_plane
{
	t_vector3				center;
	t_vector3				normal;
	int						colour;
	struct 		s_plane		*next;
}				t_plane;*/

t_plane	*parse_plane(t_data *data, char **tab)
{
	t_vector3	pos;
	t_vector3	normal;
	t_plane	*plane;

	if (ft_strslen(tab) != 4)
		corrupted(data, tab, "Bad plane format (too many args)");
	if (vec3_format(tab[1], &pos) == -1)
		corrupted(data, tab, "Bad plane position format");
	if (vec3_format(tab[2], &normal) == -1)
		corrupted(data, tab, "Bad plane normal format");
	if (check_range_vec3_orient(&normal) == -1)
		corrupted(data, tab, "plane normal not in range [-1;1]");
	if (rgb_format(tab[3]) == -1)
		corrupted(data, tab, "Bad plane rgb format");
	if (!(plane = malloc(sizeof(t_plane))))
		corrupted(data, tab, "Can't malloc plane");
	plane->center = pos;
	plane->normal = normal;
	plane->colour = str_to_rgb(tab[3]);
	return (plane);
}

void	free_plane(t_data *data)
{
	t_plane 	*next;

	while (data->planes)
	{
		next = data->planes->next;
		free(data->planes);
		data->planes = next;
	}
}

void	add_plane(t_data *data, char **tab)
{
	t_plane *tmp;

	if (data->planes == 0)
		data->planes = parse_plane(data, tab);
	else
	{
		tmp = data->planes;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_plane(data, tab);
	}
}
