/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_square.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:22 by henri             #+#    #+#             */
/*   Updated: 2020/01/25 16:27:27 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void			finish_square(t_square *square, t_vector3 orient)
{
	square->x = reorientate(newvec(1, 0, 0), orient);
	square->x = mult1vec(square->x, square->height);
	square->z = reorientate(newvec(0, 0, 1), orient);
	square->z = mult1vec(square->z, square->height);
	square->next = NULL;
}

t_square		*parse_square(t_data *data, char **tab, int fd)
{
	t_vector3	center;
	t_vector3	orient;
	t_square	*square;

	if (ft_strslen(tab) != 5)
		corrupted(data, tab, "Bad square format (too many args)", fd);
	if (vec3_format(tab[1], &center) == -1)
		corrupted(data, tab, "Bad square position format", fd);
	if (vec3_format(tab[2], &orient) == -1)
		corrupted(data, tab, "Bad cylinder orient format", fd);
	if (check_range_vec3_orient(&orient) == -1)
		corrupted(data, tab, "cylinder orient not in range [-1;1]", fd);
	if (double_format(tab[3]) == -1 || ft_atod(tab[3]) <= 0)
		corrupted(data, tab, "Bad square height format", fd);
	if (rgb_format(tab[4]) == -1)
		corrupted(data, tab, "Bad square rgb format", fd);
	if (!(square = malloc(sizeof(t_square))))
		corrupted(data, tab, "Can't malloc square", fd);
	square->center = center;
	square->normal = reorientate(newvec(0, 1, 0), orient);
	square->height = ft_atod(tab[3]);
	square->colour = str_to_rgb(tab[4]);
	finish_square(square, orient);
	//printf("Square colour : %d\n", square->colour);
	return (square);
}

void			free_square(t_data *data)
{
	t_square	*tmp;
	t_square	*next;

	tmp = data->squares;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void			add_square(t_data *data, char **tab, int fd)
{
	t_square	*tmp;

	if (data->squares == 0)
		data->squares = parse_square(data, tab, fd);
	else
	{
		tmp = data->squares;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_square(data, tab, fd);
	}
}
