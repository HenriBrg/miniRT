/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:22 by henri             #+#    #+#             */
/*   Updated: 2019/12/18 17:03:06 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
sq 	0.0,0.0,20.6 	1.0,0.0,0.0 	12.6 	255,0,255
typedef struct	s_square
{
	t_vector3				x;
	t_vector3				z;
	t_vector3				center;
	t_vector3				normal;
	double					height;
	int						colour;
	struct 		s_square	*next;
}				t_square;
*/

void 		finish_square(t_square	*square, t_vector3 orient)
{
	square->x = reorientate(newvec(1, 0, 0), orient);
	square->x = mult1vec(square->x, square->height);
	square->z = reorientate(newvec(0, 0, 1), orient);
	square->z = mult1vec(square->z, square->height);
}

t_square	*parse_square(t_data *data, char **tab)
{
	t_vector3	center;
	t_vector3	orient;
	t_square	*square;

	if (ft_strslen(tab) != 5)
		corrupted(data, tab, "Bad square format (too many args)");
	if (vec3_format(tab[1], &center) == -1)
		corrupted(data, tab, "Bad square position format");
	if (vec3_format(tab[2], &orient) == -1)
		corrupted(data, tab, "Bad cylinder orient format");
	if (check_range_vec3_orient(&orient) == -1)
		corrupted(data, tab, "cylinder orient not in range [-1;1]");
	if (double_format(tab[3]) == -1)
		corrupted(data, tab, "Bad square height format");
	if (rgb_format(tab[4]) == -1)
		corrupted(data, tab, "Bad square rgb format");
	if (!(square = malloc(sizeof(t_square))))
		corrupted(data, tab, "Can't malloc square");
	square->center = center;
	square->normal = reorientate(newvec(0, 1, 0), orient);
	square->height = ft_atod(tab[3]);
	square->colour = str_to_rgb(tab[4]);
	finish_square(square, orient);
	return (square);
}

void	free_square(t_data *data)
{
	t_square 	*next;

	while (data->squares)
	{
		next = data->squares->next;
		free(data->squares);
		data->squares = next;
	}
}

void	add_square(t_data *data, char **tab)
{
	t_square *tmp;

	if (data->squares == 0)
		data->squares = parse_square(data, tab);
	else
	{
		tmp = data->squares;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_square(data, tab);
	}
}
