/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 17:18:22 by henri             #+#    #+#             */
/*   Updated: 2019/12/18 16:20:31 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

void	free_camera(t_data *data)
{
	t_camera 	*next;

	while (data->cameras)
	{
		next = data->cameras->next;
		free(data->cameras);
		data->cameras = next;
	}
}

t_camera	*parse_camera(t_data *data, char **tab)
{
	t_vector3	pos;
	t_vector3	orient;
	t_camera	*camera;

	if (ft_strslen(tab) != 4)
		corrupted(data, tab, "Bad camera format (too many args)");
	if (vec3_format(tab[1], &pos) == -1)
		corrupted(data, tab, "Bad camera position format");
	if (vec3_format(tab[2], &orient) == -1)
		corrupted(data, tab, "Bad camera orient format");
	if (check_range_vec3_orient(&orient) == -1)
		corrupted(data, tab, "Camera orient not in range [-1;1]");
	if (double_format(tab[3]) == -1)
		corrupted(data, tab, "Bad camera fov format");
	if (!(camera = malloc(sizeof(t_camera))))
		corrupted(data, tab, "Can't malloc camera");
	camera->pos = pos;
	camera->orientation = orient;
	camera->vecx = reorientate(newvec(1, 0, 0), orient);
	camera->vecy = reorientate(newvec(0, 1, 0), orient);
	camera->vecz = reorientate(newvec(0, 0, 1), orient);
	camera->fov = ft_atod(tab[3]);
	return (camera);
}


void	add_camera(t_data *data, char **tab)
{
	t_camera *tmp;

	if (data->cameras == 0)
		data->cameras = parse_camera(data, tab);
	else
	{
		tmp = data->cameras;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = parse_camera(data, tab);
	}
}
