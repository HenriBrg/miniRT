/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:58:48 by henri             #+#    #+#             */
/*   Updated: 2019/12/19 18:13:28 by hberger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	camera_count(t_data *data)
{
	int i;
	t_camera *tmp;

	i = 0;
	tmp = data->cameras;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_camera *switch_camera(t_data *data, int camera_num)
{
	int i;
	t_camera *tmp;

	i = 1;
	tmp = data->cameras;
	while (tmp != NULL)
	{
		if (camera_num == i)
			return (tmp);
		tmp = tmp->next;
		i++;
	}
	return (data->cameras);
}

/*
void keys(int key, void *ptr)
{
	t_data	*data;

	data = (t_data*)ptr;
	if (key == KEY_ESC)
	{
		mlx_destroy_image(data->ptr, data->img);
		mlx_destroy_window(data->ptr, data->win);
		final_free(data);
		exit(0);
	}
	else if (key == KEY_ARROW_LEFT)
	{
		if (data->camera_num + 1 <= camera_count(data))
		{
			data->currentcam = currentcam->next;
			choose_camera()
		}
		else
		{

		}
	}
	else if (key == KEY_ARROW_RIGHT)
	{

	}

}

*/
