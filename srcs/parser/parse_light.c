/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:10 by henri             #+#    #+#             */
/*   Updated: 2020/01/25 15:20:29 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

t_light			*parse_light(t_data *data, char **tab, int fd)
{
	t_vector3	pos;
	t_light		*light;

	if (ft_strslen(tab) != 4)
		corrupted(data, tab, "Bad light format (too many args)", fd);
	if (vec3_format(tab[1], &pos) == -1)
		corrupted(data, tab, "Bad light position format", fd);
	if (double_format(tab[2]) == -1)
		corrupted(data, tab, "Bad light intensity format", fd);
	if (ft_atod(tab[2]) < 0 || ft_atod(tab[2]) > 1)
		corrupted(data, tab, "Light intensity not in range [-1;1]", fd);
	if (rgb_format(tab[3]) == -1)
		corrupted(data, tab, "Bad light rgb format", fd);
	if (!(light = malloc(sizeof(t_light))))
		corrupted(data, tab, "Can't malloc light", fd);
	light->pos = pos;
	light->ratio = ft_atod(tab[2]);
	light->colour = intensity(str_to_rgb(tab[3]), light->ratio);
	light->next = NULL;
	return (light);
}

void			free_light(t_data *data)
{
	t_light		*tmp;
	t_light		*next;

	tmp = data->lights;
	if (tmp == NULL)
		return ;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
}

void			add_light(t_data *data, char **tab, int fd)
{
	t_light		*tmp;

	if (data->lights == 0)
		data->lights = parse_light(data, tab, fd);
	else
	{
		tmp = data->lights;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_light(data, tab, fd);
	}
}
