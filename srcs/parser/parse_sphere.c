/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:19 by henri             #+#    #+#             */
/*   Updated: 2020/01/27 16:42:37 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

void			addcylsphere(t_data *data, t_sphere *sphere)
{
	t_sphere	*tmp;

	if (data->spheres == 0)
		data->spheres = sphere;
	else
	{
		tmp = data->spheres;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = sphere;
	}
}

t_sphere		*parse_sphere(t_data *data, char **tab, int fd)
{
	t_vector3	center;
	t_sphere	*sphere;

	if (ft_strslen(tab) != 4)
		corrupted(data, tab, "Bad sphere format (too many args)", fd);
	if (vec3_format(tab[1], &center) == -1)
		corrupted(data, tab, "Bad sphere position format", fd);
	if (double_format(tab[2]) == -1 || ft_atod(tab[2]) <= 0)
		corrupted(data, tab, "Bad sphere radius format", fd);
	if (rgb_format(tab[3]) == -1)
		corrupted(data, tab, "Bad sphere rgb format", fd);
	if (!(sphere = malloc(sizeof(t_sphere))))
		corrupted(data, tab, "Can't malloc sphere", fd);
	sphere->center = center;
	sphere->next = NULL;
	sphere->radius = ft_atod(tab[2]);
	sphere->colour = str_to_rgb(tab[3]);
	return (sphere);
}

void			free_sphere(t_data *data)
{
	t_sphere	*tmp;
	t_sphere	*next;

	tmp = data->spheres;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void			add_sphere(t_data *data, char **tab, int fd)
{
	t_sphere	*tmp;

	if (data->spheres == 0)
		data->spheres = parse_sphere(data, tab, fd);
	else
	{
		tmp = data->spheres;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_sphere(data, tab, fd);
	}
}
