/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:58:48 by henri             #+#    #+#             */
/*   Updated: 2020/01/27 14:24:27 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/mini_rt.h"

int				camera_count(t_data *data)
{
	int			i;
	t_camera	*tmp;

	i = 0;
	tmp = data->cameras;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_camera		*get_current_camera(t_data *data)
{
	int			i;
	t_camera	*tmp;

	i = 1;
	tmp = data->cameras;
	while (tmp != NULL)
	{
		if (data->camera_num == i)
			return (tmp);
		tmp = tmp->next;
		i++;
	}
	return (data->cameras);
}

int				keys(int key, void *ptr)
{
	t_data		*data;

	data = (t_data*)ptr;
	if (key == KEY_ESC)
	{
		clear(data);
		exit(0);
	}
	else if (key == KEY_SPACE)
	{
		if (camera_count(data) == 1)
			return (write(1, "You declared only one camera\n", 30));
		else if (data->camera_num + 1 <= camera_count(data))
			data->camera_num += 1;
		else
			data->camera_num = 1;
		raytrace(data);
		mlx_put_image_to_window(data->ptr, data->win, data->img, 0, 0);
	}
	return (0);
}

int				clearbis(t_data *data)
{
	if (data->img != 0)
		mlx_destroy_image(data->ptr, data->img);
	free(data->res);
	free(data->amb);
	free_camera(data);
	free_light(data);
	free_sphere(data);
	free_plane(data);
	free_square(data);
	free_triangle(data);
	free_cylinder(data);
	free(data);
	exit(0);
}
