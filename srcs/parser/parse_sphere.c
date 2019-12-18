/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:19 by henri             #+#    #+#             */
/*   Updated: 2019/12/18 19:23:43 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
sp 0.0,0.0,20.6 12.6 10,0,255
typedef struct	s_sphere
{
	t_vector3				center;
	double					radius;
	int						colour;
	struct 		s_sphere	*next;
}				t_sphere;
*/

t_sphere	*parse_sphere(t_data *data, char **tab)
{
	t_vector3	center;
	t_sphere	*sphere;

	if (ft_strslen(tab) != 4)
		corrupted(data, tab, "Bad sphere format (too many args)");
	if (vec3_format(tab[1], &center) == -1)
		corrupted(data, tab, "Bad sphere position format");
	if (double_format(tab[2]) == -1)
		corrupted(data, tab, "Bad sphere radius format");
	if (rgb_format(tab[3]) == -1)
		corrupted(data, tab, "Bad sphere rgb format");
	if (!(sphere = malloc(sizeof(t_sphere))))
		corrupted(data, tab, "Can't malloc sphere");
	sphere->center = center;
	sphere->radius = ft_atod(tab[2]);
	sphere->colour = str_to_rgb(tab[3]);
	return (sphere);
}

void	free_sphere(t_data *data)
{
	t_sphere 	*tmp;
	t_sphere 	*next;

	tmp = data->spheres;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void	add_sphere(t_data *data, char **tab)
{
	t_sphere *tmp;

	if (data->spheres == 0)
		data->spheres = parse_sphere(data, tab);
	else
	{
		tmp = data->spheres;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_sphere(data, tab);
	}
}
