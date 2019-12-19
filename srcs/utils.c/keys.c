/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henri <henri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 22:58:48 by henri             #+#    #+#             */
/*   Updated: 2019/12/18 23:46:07 by henri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
