/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:25 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 22:32:16 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
tr 	10.0,20.0,10.0 	10.0,10.0,20.0 	20.0,10.0,10.0 	0,0,255

typedef struct	s_triangle
{
	t_vector3				p1;
	t_vector3				p2;
	t_vector3				p3;
	t_vector3				normal;
	int						colour;
	struct 		s_triangle	*next;
}				t_triangle;

*/

t_triangle	*parse_triangle(t_data *data, char **tab, int fd)
{
	t_vector3	pos1;
	t_vector3	pos2;
	t_vector3	pos3;
	t_triangle	*triangle;

	if (ft_strslen(tab) != 5)
		corrupted(data, tab, "Bad triangle format (too many args)", fd);
	if (vec3_format(tab[1], &pos1) == -1)
		corrupted(data, tab, "Bad triangle position1 format", fd);
	if (vec3_format(tab[2], &pos2) == -1)
		corrupted(data, tab, "Bad triangle position2 format", fd);
	if (vec3_format(tab[3], &pos3) == -1)
		corrupted(data, tab, "Bad triangle position3 format", fd);
	if (rgb_format(tab[4]) == -1)
		corrupted(data, tab, "Bad triangle rgb format", fd);
	if (!(triangle = malloc(sizeof(t_triangle))))
		corrupted(data, tab, "Can't malloc triangle", fd);
	triangle->p1 = pos1;
	triangle->p2 = pos2;
	triangle->p3 = pos3;
	triangle->next = NULL;
	triangle->colour = str_to_rgb(tab[4]);
	return (triangle);
}

void	free_triangle(t_data *data)
{
	t_triangle 	*tmp;
	t_triangle 	*next;

	tmp = data->triangles;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	add_triangle(t_data *data, char **tab, int fd)
{
	t_triangle *tmp;

	if (data->triangles == 0)
		data->triangles = parse_triangle(data, tab, fd);
	else
	{
		tmp = data->triangles;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_triangle(data, tab, fd);
	}
}
