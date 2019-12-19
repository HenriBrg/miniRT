/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 18:09:10 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 18:16:04 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/*
l -40.0,50.0,0.0 0.6 10,0,255
typedef struct	s_light
{
	t_vector3	pos;
	double		ratio;
	int			colour;
	struct 		s_light		*next;
}				t_light;
*/

t_light	*parse_light(t_data *data, char **tab)
{
	t_vector3	pos;
	t_light		*light;

	if (ft_strslen(tab) != 4)
		corrupted(data, tab, "Bad light format (too many args)");
	if (vec3_format(tab[1], &pos) == -1)
		corrupted(data, tab, "Bad light position format");
	if (double_format(tab[2]) == -1)
		corrupted(data, tab, "Bad light intensity format");
	if (rgb_format(tab[3]) == -1)
		corrupted(data, tab, "Bad light rgb format");
	if (!(light = malloc(sizeof(t_light))))
		corrupted(data, tab, "Can't malloc light");
	light->pos = pos;
	light->ratio = ft_atod(tab[2]);
	light->colour = str_to_rgb(tab[3]);
	light->next = NULL;
	return (light);
}

void	free_light(t_data *data)
{
	t_light 	*tmp;
	t_light 	*next;

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

void	add_light(t_data *data, char **tab)
{
	t_light *tmp;

	if (data->lights == 0)
		data->lights = parse_light(data, tab);
	else
	{
		tmp = data->lights;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_light(data, tab);
	}
}
